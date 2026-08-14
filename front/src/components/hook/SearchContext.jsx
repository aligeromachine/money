import { createContext, useState, useContext, useCallback } from 'react';
import { dateUtils } from '../../utils/func';

// Создаем контекст с начальными значениями
const SearchContext = createContext({
    isModalOpen: false,
    openModal: () => {},
    closeModal: () => {},
    formData: {},
    onChange: () => {},
});

// Провайдер для управления состоянием модалки
export const SearchProvider = ({ children }) => {
    const [formData, setForm] = useState({});
    const [isModalOpen, setIsModalOpen] = useState(false);

    const openModal = useCallback((response) => {
        setForm({ ...formData, ...response });
        setIsModalOpen(!isModalOpen);
    }, []);

    const closeModal = useCallback(() => {
        setForm({});
        setIsModalOpen(false);
    }, []);

    const onChange = e => {
        if (e.target.type === 'checkbox') {
            const v = e.target.value === 'false' ? true : false;
            setForm({ ...formData, [e.target.name]: v });
        } else {
            setForm({ ...formData, [e.target.name]: e.target.value });
        }
    };

    return (
        <SearchContext.Provider
            value={{
                isModalOpen,
                openModal,
                closeModal,
                formData,
                onChange,
            }}
        >
            {children}
        </SearchContext.Provider>
    );
};

// Кастомный хук для удобного доступа к контексту
export const useSearchContent = () => {
    return useContext(SearchContext);
};
