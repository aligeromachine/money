import React from 'react';
import { useSearchContent } from '../../../../components/hook/SearchContext';
import { editSearchRow } from '../../../../services/search/request';
import { SearchModalContent } from './Content';
import { UseValid } from './Validate';

export const SearchModal = () => {
    const { isModalOpen, closeModal, formData, onChange } = useSearchContent();
    const { validate, validateForm, repErr, setRepErr } = UseValid();

    async function onAdd() {
        if (!validateForm(formData)) {
            return;
        }

        const response = await editSearchRow(formData.pk, formData);
        if (response.data === 'err') {
            setRepErr(response.message);
            return;
        }
        closeModal();
    }

    return (
        <SearchModalContent
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
