from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.shop.model import ShopMessage
from api.back.shop.base import add_shop_data, delete_shop_row, edit_shop_data, get_shop_row, list_shop_data
from api.back.shop.table import table_shop_data
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(ShopMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: ShopMessage) -> dict | list:
    respo = {"data": "err", "message": "undefinded"}

    if item.command == CmdRouter.table:
        respo = table_shop_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_shop_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_shop_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_shop_row(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_shop_data(item=item)

    if item.command == CmdRouter.listkeys:
        respo = list_shop_data(item=item)

    return respo
