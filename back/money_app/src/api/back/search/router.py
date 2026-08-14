from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.search.model import SearchMessage
from api.back.search.base import delete_search_row, edit_search_data, get_search_row, list_search_data
from api.back.search.table import table_search_data
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(SearchMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: SearchMessage) -> dict | list:
    respo = {"data": "err", "message": "undefinded"}

    if item.command == CmdRouter.table:
        respo = table_search_data(item=item)

    if item.command == CmdRouter.listkeys:
        respo = list_search_data()

    if item.command == CmdRouter.delete:
        respo = delete_search_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_search_row(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_search_data(item=item)

    return respo
