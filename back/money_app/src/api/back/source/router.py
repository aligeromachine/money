from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.source.model import SourceMessage
from api.back.source.base import add_source_data, delete_source_row, edit_source_data, get_source_row, list_source_data
from api.back.source.table import table_source_data
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(SourceMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: SourceMessage) -> dict | list:
    respo = {"data": "err", "message": "undefinded"}

    if item.command == CmdRouter.table:
        respo = table_source_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_source_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_source_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_source_row(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_source_data(item=item)

    if item.command == CmdRouter.listkeys:
        respo = list_source_data(item=item)

    return respo
