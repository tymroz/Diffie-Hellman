public abstract class Field {
    public abstract void setValue(int value);
    public abstract int getValue();
    public abstract int getCharacteristic();
    public abstract Field add(final Field obj);
    public abstract Field sub(final Field obj);
    public abstract Field mult(final Field obj);
    public abstract Field div(final Field obj);
    public abstract void assign(final Object obj);
    public abstract void multAndAssign(final Field obj);
    public abstract void divAndAssign(final Field obj);
    public abstract void addAndAssign(final Field obj);
    public abstract void subAndAssign(final Field obj);
    public abstract boolean ifNotEqual(final Object b);
    public abstract boolean ifEqual(final Object b);
    public abstract boolean ifLessEqual(final Object b);
    public abstract boolean ifGreaterEqual(final Object b);
    public abstract boolean ifLess(final Object b);
    public abstract boolean ifGreater(final Object b);
}