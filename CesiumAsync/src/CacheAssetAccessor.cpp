#include "CesiumAsync/CacheAssetAccessor.h"
#include "CesiumAsync/AsyncSystem.h"
#include "CesiumAsync/IAssetResponse.h"
#include "CesiumAsync/CacheItem.h"

namespace CesiumAsync {
	class CacheAssetResponse : public IAssetResponse {
    public:
        CacheAssetResponse(const CacheItem* pCacheItem) 
			: _pCacheItem{pCacheItem}
		{}

		virtual uint16_t statusCode() const override { 
			return this->_pCacheItem->cacheResponse().statusCode(); 
		}

		virtual const std::string& contentType() const override {
			return this->_pCacheItem->cacheResponse().contentType(); 
		}

		virtual const std::map<std::string, std::string>& headers() const override {
			return this->_pCacheItem->cacheResponse().headers(); 
		}

		virtual const ResponseCacheControl* cacheControl() const override {
			return this->_pCacheItem->cacheResponse().cacheControl(); 
		}

		virtual gsl::span<const uint8_t> data() const override {
			return this->_pCacheItem->cacheResponse().data(); 
		}

    private:
        const CacheItem* _pCacheItem;
	};

	class CacheAssetRequest : public IAssetRequest 
	{
	public:
        CacheAssetRequest(CacheItem cacheItem) 
			: _cacheItem{std::move(cacheItem)}
		{
			_response = std::make_optional<CacheAssetResponse>(&this->_cacheItem.value());
		}

		virtual const std::string& method() const override {
			return this->_cacheItem->cacheRequest().method();
		}

		virtual const std::string& url() const override {
			return this->_cacheItem->cacheRequest().url();
		}

		virtual const std::map<std::string, std::string>& headers() const override {
			return this->_cacheItem->cacheRequest().headers();
		}

		virtual const IAssetResponse* response() const override {
			return &_response.value();
		}

	private:
		std::optional<CacheAssetResponse> _response;
        std::optional<CacheItem> _cacheItem;
	};

	CacheAssetAccessor::CacheAssetAccessor(
		std::unique_ptr<IAssetAccessor> assetAccessor,
		std::unique_ptr<ICacheDatabase> cacheDatabase) 
		: _pAssetAccessor{ std::move(assetAccessor) }
		, _pCacheDatabase{std::move(cacheDatabase)}
	{
	}

	CacheAssetAccessor::~CacheAssetAccessor() noexcept {}

	void CacheAssetAccessor::requestAsset(const AsyncSystem* pAsyncSystem, 
		const std::string& url, 
		const std::vector<THeader>& headers,
		std::function<void(std::shared_ptr<IAssetRequest>)> callback) 
	{
		pAsyncSystem->runInWorkerThread([this, pAsyncSystem, url, headers, callback]() -> std::optional<CacheItem> {
			bool readError = false;
			std::string error;
			std::optional<CacheItem> cacheItem;
			if (!this->_pCacheDatabase->getEntry(url, cacheItem, error)) {
				// TODO: log error
				readError = true;
			}

			if (!cacheItem) {
				ICacheDatabase* pCacheDatabase = this->_pCacheDatabase.get();
				this->_pAssetAccessor->requestAsset(pAsyncSystem, 
					url, 
					headers, 
					[pAsyncSystem, pCacheDatabase, callback, readError](std::shared_ptr<IAssetRequest> pCompletedRequest) {
						// cache doesn't have it or the cache item is stale, so request it
						if (!readError && shouldCacheRequest(*pCompletedRequest)) {
							pAsyncSystem->runInWorkerThread([pCacheDatabase, pCompletedRequest]() {
								std::string error;
								if (!pCacheDatabase->storeResponse(pCompletedRequest->url(),
									calculateExpiryTime(*pCompletedRequest),
									*pCompletedRequest,
									error))
								{
									// TODO: log error here
								}
							});
						}

						callback(pCompletedRequest);
					});
			}

			return cacheItem;
		}).thenInMainThread([callback](std::optional<CacheItem> &&cacheItem) {
			if (cacheItem) {
				callback(std::make_unique<CacheAssetRequest>(std::move(cacheItem.value())));
			}
		});
	}

	void CacheAssetAccessor::tick() noexcept {
		_pAssetAccessor->tick();
	}

	/*static*/ bool CacheAssetAccessor::isCacheValid(const CacheItem& /*cacheItem*/) {
		return true;
	}

	/*static*/ bool CacheAssetAccessor::shouldCacheRequest(const IAssetRequest& /*request*/) {
		return true;
	}

	/*static*/ std::time_t CacheAssetAccessor::calculateExpiryTime(const IAssetRequest& /*request*/) {
		return std::time(0);
	}
}