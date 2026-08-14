import logging
from datetime import datetime
from api.back.buy.model import BuySignal
from machine.shift.model.buy import MacBuyShift
from money.models import Buy, Shop, Catalog
from api.back.search.model import SearchMessage
from api.back.model import KeyValue
from api.back.buy.query import BUY_ROW

logger = logging.getLogger(__name__)

@MacBuyShift.row_change  # type: ignore
def delete_search_row(item: SearchMessage) -> dict:
    Buy.objects.filter(pk=item.pk).delete()
    return dict(data='ok', message=f'delete search key: {item.pk}')

@MacBuyShift.row_save_redis  # type: ignore
def get_search_row(item: SearchMessage) -> dict:
    data: dict = {}
    for it in Buy.objects.raw(raw_query=BUY_ROW, params=[item.pk]):
        data = BuySignal.from_orm(it).model_dump()
    return data

@MacBuyShift.row_edit  # type: ignore
def edit_search_data(item: SearchMessage) -> dict:
    try:
        elem = Buy.objects.get(pk=item.pk)

        elem.title = item.title
        elem.amount = item.amount
        elem.shop_id = item.shop
        elem.products_id = item.prod
        if isinstance(item.created, datetime):
            elem.created = item.created
        elem.save()
    except: # noqa
        return dict(data='err', message='pk does not exist')

    return dict(data='ok', message=f'update {item.pk=}')

def list_search_data() -> dict:
    org = [KeyValue(value=it.pk, label=it.title).model_dump() for it in Shop.objects.all().order_by('title')]
    prod = [KeyValue(value=it.pk, label=it.title).model_dump() for it in Catalog.objects.all().order_by('title')]
    return dict(groupOrganization=org, groupTypeProd=prod)
