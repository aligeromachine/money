from django.db import connection
from typing import Generator
from libs.django.model import CalcCountSQL

def raw_query_generator(sql: str, params: tuple | None = None, fetch_size: int = 1000) -> Generator[tuple, None, None]:
    with connection.cursor() as cursor:
        cursor.itersize = fetch_size if fetch_size > 0 else 1
        cursor.execute(sql, params)
        for row in cursor:
            yield row

def count_raw_query(sql: str, params: tuple | None = None) -> int:
    count: int = 0
    for it in raw_query_generator(sql=sql, params=params):
        count = CalcCountSQL.from_raw_array(it).value
    return count
