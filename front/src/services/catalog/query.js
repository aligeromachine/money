import { postRequestCheck } from '../../utils/requests';
import { URL, CmdType } from '../const';

export const getCatalogOptions = async () => {
    const params = {
        command: CmdType.listkeys,
    };
    const response = await postRequestCheck(URL.cat, params);
    if (!response) return Promise.reject('Error response');
    return response;
};
