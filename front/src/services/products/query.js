import { postRequestCheck } from '../../utils/requests';
import { URL, CmdType } from '../const';

export const getProdOptions = async pk => {
    const params = {
        command: CmdType.listkeys,
        pk,
    };
    const response = await postRequestCheck(URL.products, params);
    if (!response) return Promise.reject('Error response');
    return response;
};
