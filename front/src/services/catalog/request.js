import { postRequestCheck } from '../../utils/requests';
import { store } from '../store';
import { setRowState, setRowPk } from '../utils/row/state';
import { getCatTable } from './state';
import { URL, CmdType } from '../const';

export const addCatRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.cat, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getCatTable());
    return response;
};

export const deleteCatRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.cat, params);
    await store.dispatch(getCatTable());
};

export const getCatRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.cat, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
