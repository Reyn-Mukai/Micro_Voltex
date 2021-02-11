#ifndef UTILITY_H
#define UTILITY_H

template<typename T>
class Option{

    public:
        Option();
        Option( const T value );
        Option( Option<T>& optionValue );
        Option( Option<T>&& optionValue );
        Option<T>& operator=( const T& value );
        Option<T>& operator=( const Option<T>& optionValue );
        void setValue( const T value );
        void setValue( const Option& optionValue );
        bool tryGetValue( T& returnValue ) const;
        
    private:
        T value;
        bool isNone;

};

template<typename T>
Option<T>::Option( const T value ) : value(value), isNone(false) {}

template<typename T>
Option<T>::Option() : value(0), isNone(true) {}


template<typename T>
Option<T>::Option( Option<T>& optionValue ){
    this->setValue(optionValue);
}

template<typename T>
Option<T>::Option( Option<T>&& optionValue ){
    this->setValue(optionValue);
}

template<typename T>
Option<T>& Option<T>::operator=( const T& value ){
    if (this == &value) return *this;
    else this->setValue(value);
    return *this;
}

template<typename T>
Option<T>& Option<T>::operator=( const Option<T>& optionValue ){
    this->setValue(optionValue);
    return *this;
}

template<typename T>
void Option<T>::setValue( const T value ){
    this->isNone = false;
    this->value = value;
}

template<typename T>
void Option<T>::setValue( const Option<T>& optionValue ){
    this->isNone = optionValue.isNone;
    this->value = optionValue.value;
}

template<typename T>
bool Option<T>::tryGetValue( T& returnValue ) const {
    if(this->isNone) {
        return false;
    } else {
        returnValue = this->value;
        return true;
    }
}


#endif
