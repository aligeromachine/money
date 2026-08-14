import styles from './Strip.module.css';

export const BlueStrip = () => {
  return <div className={`${styles.Strip} ${styles.bgcBlue}`} />;
};

export const RedStrip = () => {
  return <div className={`${styles.Strip} ${styles.bgcred}`} />;
};
