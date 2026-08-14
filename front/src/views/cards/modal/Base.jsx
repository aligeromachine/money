import React from 'react';
import { useModalContent } from '../../../components/hook/ModalContext';
import { addCardsRow } from '../../../services/cards/request';
import { setRowState } from '../../../services/utils/row/state';
import { CardsContent } from './Content';
import { UseValid } from './Validate';

export const CardsModal = () => {
    const { isModalOpen, closeModal, formData, onChange, onSet, isEdit } = useModalContent();
    const { validate, validateForm, repErr, setRepErr } = UseValid();

    async function onAdd() {
        if (!validateForm(formData)) {
            return;
        }

        onSet(setRowState);
        const response = await addCardsRow();
        if (response.data === 'err') {
            setRepErr(response.message);
            return;
        }
        if (isEdit) {
            closeModal();
        }
    }

    return (
        <CardsContent
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
