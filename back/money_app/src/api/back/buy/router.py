from django.http import HttpRequest
from api.back.decore import validate_model
from api.back.buy.table import table_buy_data
from api.back.buy.model import BuyMessage
from api.back.buy.base import add_buy_data, delete_buy_row, edit_buy_data, get_buy_row
from api.back.const import CmdRouter

@validate_model(BuyMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: BuyMessage) -> dict | list:
    respo = dict(data="err", message="undefinded")

    if item.command == CmdRouter.table:
        respo = table_buy_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_buy_data(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_buy_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_buy_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_buy_row(item=item)

    return respo
