import logging
from django.contrib.auth.models import User
from django.db.models import Model
from django.http import HttpRequest
from libs.const import CONST

logger = logging.getLogger(__name__)

def RULES_ROUTE(user: str) -> list:
    for it in User.objects.filter(username=user):
        return str(it.last_name).split(',')
    return []

def is_super_user(user: str) -> bool:
    for it in User.objects.filter(username=user):
        return bool(it.is_superuser)
    return False

def UpdateSQl(query: str, values: list) -> None:
    from django.db import connection
    with connection.cursor() as cursor:
        cursor.execute(query, values)

def count_raw_sql(model: type[Model], sql: str, params: list = []) -> int:
    count: int = 0
    for it in model.objects.raw(raw_query=sql, params=params):
        count = it.c
    return count

def get_client_ip(request: HttpRequest) -> str:
    if not request:
        return str(CONST.localhost)
    ip: str = ''
    x_forwarded_for = request.META.get('HTTP_X_FORWARDED_FOR')
    if x_forwarded_for:
        # X-Forwarded-For может содержать цепочку: client, proxy1, proxy2
        # IP клиента — это первый адрес в списке
        ip = str(x_forwarded_for).split(',')[0].strip()
    else:
        ip = request.META.get('REMOTE_ADDR')
    return ip
