import logging
from libs.validate.exp import validate_list
from machine.tools.model import FinStat, WidgetRange
from machine.tools.query import GROUP_USER_YEAR_BUY_PROFIT
from money.models import AuditFin, Buy

logger = logging.getLogger(__name__)

def list_audit() -> list[FinStat]:
    ls: list[FinStat] = [FinStat.from_orm(it) for it in Buy.objects.raw(raw_query=GROUP_USER_YEAR_BUY_PROFIT)]
    return ls


def get_list_user_finance(user_id: int) -> list[WidgetRange]:
    finance_years: list[WidgetRange] = []
    for it in AuditFin.objects.filter(user_id=user_id):
        raw = validate_list(it.payload, WidgetRange, prn=True)
        if isinstance(raw, list):
            finance_years = raw
    return finance_years
