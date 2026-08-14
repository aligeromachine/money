import { apiClient } from '../../../utils/requests';
import { URL } from '../../const';

export const getVersion = async () => {
    const response = await apiClient.get(URL.version);
    if (!response) return Promise.reject('Error response');
    return response;
};
