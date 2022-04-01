#ifndef GPIO_H
#define GPIO_H

#include <QObject>

class gpio : public QObject
{
    Q_OBJECT
public:
    explicit gpio(QObject *parent = nullptr); // constructor
    ~gpio(); // destructor for clean-up
    void set(int pin, bool value);
    void set(unsigned int pattern);
    bool get(int pin);

    bool detect_edge(int pin, bool edge, int idx);  //edge = false => falling  edge = true => rising

private:

    int m_handle;

    QList<bool> m_oldState = {true, true, true};
};

#endif // GPIO_H
