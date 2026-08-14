import React from 'react';
import { useModalContent } from '../../../../components/hook/ModalContext';
import { setRowState } from '../../../../services/utils/row/state';
import { addProfitRow } from '../../../../services/profit/request';
import { ProfitContent } from './Content';
import { UseValid } from './Validate';

export const ProfitModal = () => {
    const { isModalOpen, closeModal, formData, onChange, onSet, isEdit } = useModalContent();
    const { validate, validateForm, repErr, setRepErr } = UseValid();

    async function onAdd() {
        if (!validateForm(formData)) {
            return;
        }

        onSet(setRowState);
        const response = await addProfitRow();
        if (response.data === 'err') {
            setRepErr(response.message);
            return;
        }
        if (isEdit) {
            closeModal();
        }
    }

    return (
        <ProfitContent
            visible={isModalOpen}
            onClose={closeModal}
            formData={formData}
            onChange={onChange}
            validate={validate}
            repErr={repErr}
            onAdd={onAdd}
        />
    );
};
