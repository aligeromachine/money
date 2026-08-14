from typing import Callable, Any, Self, Concatenate
import orjson
import requests
from requests.exceptions import RequestException, ConnectionError, Timeout, HTTPError
from functools import wraps
import logging
import urllib3
from libs.types.exp import P, JsonType, ResponseFunc, ResponseRequest
from libs.decore.lam import dump_model
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

logger = logging.getLogger(__name__)

class Config:
    API_TIMEOUT: int = 5
    API_HEADERS: dict = {
        "Content-Type": "application/json", 
        "Cache-Control": "no-cache",
        "Accept": "*/*",
    }
    API_HEADERS_MOZILA: dict = {
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0", 
        "Accept": "application/json, text/plain, */*", 
        "Accept-Language": "en-US,en;q=0.5",
        "Accept-Encoding": "gzip, deflate",
        "Connection": "keep-alive",
    }

class HttpClient:
    def __init__(self) -> None:
        self.timeout = Config.API_TIMEOUT
        self.chunk_size = 5 * 1024_1024

        self.session = requests.Session()
        self.session.headers.update(Config.API_HEADERS)
        self.session.verify = False

    def __enter__(self) -> Self:
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:  # type: ignore
        self.session.close()

    def _request(self, method: str, url: str, **kwargs: Any) -> ResponseRequest:
        kwargs.setdefault('timeout', self.timeout)

        response = None
        data_content: bytes = b''
        try:
            response = self.session.request(method, url, **kwargs)
            if kwargs.get('stream'):
                for chunk in response.iter_content(chunk_size=self.chunk_size):
                    if chunk:
                        data_content += chunk
            else:
                response.raise_for_status()
        except requests.HTTPError as exc:
            logger.error(f"Session HTTP: {exc.request.url}, {exc.request.method}")
        except Exception as exc:
            logger.error(f"Session An occurred: {exc}")

        if data_content:
            return data_content

        if response and response.text:
            respo = orjson.loads(response.content)
            return respo

        return None

    def is_url_available(self, url: str) -> bool:
        try:
            response = self.session.head(url, timeout=self.timeout, allow_redirects=True)
            return 200 <= response.status_code < 400
        except (ConnectionError, Timeout, HTTPError, RequestException) as e:
            logger.warning(f"URL недоступен: {url} -> {e}")
            return False

    def is_connect(self, url: str) -> bool:
        try:
            response = self.session.head(url, timeout=self.timeout, allow_redirects=True)
            return bool(response.status_code)
        except (ConnectionError, Timeout):
            return False

    def get(self, url: str, params: JsonType = None, **kwargs: Any) -> ResponseRequest:
        return self._request('GET', url, params=dump_model(params), **kwargs)

    def post(self, url: str, json: JsonType = None, **kwargs: Any) -> ResponseRequest:
        return self._request('POST', url, json=dump_model(json), **kwargs)

    def put(self, url: str, data: JsonType = None, **kwargs: Any) -> ResponseRequest:
        return self._request('PUT', url, data=dump_model(data), **kwargs)

    def patch(self, url: str, data: JsonType = None, **kwargs: Any) -> ResponseRequest:
        return self._request('PATCH', url, data=dump_model(data), **kwargs)

    def delete(self, url: str, **kwargs: Any) -> ResponseRequest:
        return self._request('DELETE', url, **kwargs)

    def post_data(self, url: str, data: JsonType = None, **kwargs: Any) -> ResponseRequest:
        return self._request('POST', url, data=dump_model(data), **kwargs)

def http_client(func: Callable[Concatenate[HttpClient, P], ResponseFunc]) -> Callable[P, ResponseFunc]:  # type: ignore
    @wraps(func)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> ResponseFunc:
        with HttpClient() as client:
            # kwargs.setdefault('client', client)
            return func(client, *args, **kwargs)
    return wrapper

@http_client
def http_get(client: HttpClient, url: str, data: JsonType = None) -> ResponseRequest:
    return client.get(url, data)

@http_client
def http_post(client: HttpClient, url: str, json: JsonType = None) -> ResponseRequest:
    return client.post(url, json)


# USE CASE
# from typing import Any
# from request.http_client import HttpClient, http_client, http_get

# @http_client
# def fetch_posts(client: HttpClient, *args: Any, **kwargs: Any):
#     respo = client.get("https://jsonplaceholder.typicode.com/users")
#     print(respo)
#     # respo = client.get("https://jsonplaceholder.typicode.com/posts")
#     # print(respo)

# def main():

#     # respo = http_get("https://jsonplaceholder.typicode.com//users")
#     # print(respo)

#     respo = http_get("https://jsonplaceholder.typicode.com/posts2")
#     print(respo)

# if __name__ == "__main__":
#     main()
