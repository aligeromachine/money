from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.profit.base import add_profit_data, delete_profit_row, edit_profit_data, get_profit_row
from api.back.profit.table import table_profit_data
from api.back.profit.model import ProfitMessage
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(ProfitMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: ProfitMessage) -> dict | list:
    respo = {"data": "err", "message": "undefinded"}

    if item.command == CmdRouter.table:
        respo = table_profit_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_profit_data(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_profit_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_profit_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_profit_row(item=item)

    return respo
