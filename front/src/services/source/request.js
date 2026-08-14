import { postRequestCheck } from '../../utils/requests';
import { setRowState, setRowPk } from '../utils/row/state';
import { store } from '../store';
import { URL, CmdType } from '../const';
import { getSourceTable } from './state';

export const addSourceRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.source, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getSourceTable());
    return response;
};

export const deleteSourceRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.source, params);
    await store.dispatch(getSourceTable());
};

export const getSourceRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.source, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
