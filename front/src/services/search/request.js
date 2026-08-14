import { postRequestCheck } from '../../utils/requests';
import { create_params } from '../../utils/func';
import { URL, CmdType } from '../const';

export const getSearchTable = async (offset, limit, form_data) => {
    const params = {
        command: CmdType.table,
        offset,
        limit,
        form_data
    };
    const response = await postRequestCheck(URL.search, params);
    if (!response) return Promise.reject('Error response');
    return response;
};

export const deleteSearchRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.search, params);
};

export const getSearchRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.search, params);
    return response;
};

export const editSearchRow = async (pk, formData) => {
    const params = {
        command: CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.search, params);
    if (!response) return Promise.reject('Error response');
    return response;
};
