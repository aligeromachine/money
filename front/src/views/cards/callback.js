import { setCardEnableStatus } from '../../services/cards/request';

export const ChangeStatusEnable = ({ checked, pk }) => {
    setCardEnableStatus(checked, pk);
};
