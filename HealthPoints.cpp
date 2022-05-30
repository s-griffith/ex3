#include "HealthPoints.h"

//Constructor for HealthPoints class
HealthPoints::HealthPoints(int hpoints /* =DEFAULT_HP */)
{
    if (hpoints <= 0) {
        throw InvalidArgument();
    }
    m_hp = hpoints;
    m_maxHP = hpoints;
}

// "+=" operator (hp1 += 50)
HealthPoints& HealthPoints::operator+=(int addition)
{
    if (m_hp + addition >= m_maxHP) {
        m_hp = m_maxHP;
    }
    else if (m_hp + addition <= 0) {
        m_hp = 0;
    }
    else {
        m_hp += addition;
    }
    return *this;
}

// "-=" operator (hp1 -= 50)
HealthPoints& HealthPoints::operator-=(int subtraction)
{
    if (m_hp - subtraction >= m_maxHP) {
        m_hp = m_maxHP;
    }
    else if (m_hp - subtraction <= 0) {
        m_hp = 0;
    }
    else {
        m_hp -= subtraction;
    }
    return *this;
}

// "+" operator with HP object first (hp1 = hp1 + 50)
HealthPoints HealthPoints::operator+(int addition) const
{
    HealthPoints new_hp(*this);
    new_hp += addition;
    return new_hp;
}

// "-" operator with HP object first (hp1 = hp1 - 50)
HealthPoints HealthPoints::operator-(int subtraction) const
{
    HealthPoints new_hp(*this);
    new_hp -= subtraction;
    return new_hp;
}

//------------------------------Friend Non-Member Functions-------------------------------

// "<" operator between two HP objects (comparison = (hp1 < hp2))
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2) //what about max_hp?
{
    return (hp1.m_hp < hp2.m_hp);
}

// Output stream operator in the format: "<currentHealthPoints>(<maximumHealthPoints>)"
std::ostream& operator<<(std::ostream& os, const HealthPoints& hp1)
{
    os << hp1.m_hp << "(" << hp1.m_maxHP << ")";
    return os;
}

//---------------------------Non-Friend Non-Member Functions-----------------------------

// "+" operator with HP object second (hp1 = 50 + hp1)
HealthPoints operator+(int addition, const HealthPoints& hp1)
{
    HealthPoints new_hp = hp1;
    new_hp += addition;
    return new_hp;
}

// "==" operator (comparison = (hp1 == hp2);   comparison = (100 == hp1);   comparison = (hp1 == 100))
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !((hp1 < hp2) || (hp2 < hp1));
}

// "!=" operator (comparison = (hp1 != hp2);   comparison = (100 != hp1);   comparison = (hp1 != 100))
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 == hp2);
}

// "<=" operator between two HP objects (comparison = (hp1 <= hp2))
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return ((hp1 < hp2) || (hp1 == hp2));
}

// ">" operator between two HP objects (comparison = (hp1 > hp2))
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 <= hp2);
}

// ">=" operator between two HP objects (comparison = (hp1 >= hp2))
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    return !(hp1 < hp2);
}