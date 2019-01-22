#ifndef VECTOR3_H
#define VECTOR3_H
#include "typedefs.h"
class Vector3
{
public:
    float__ a[3];
    Vector3();
    Vector3(float__ a0,float__ a1,float__ a2);
    virtual ~Vector3();
    int__ Size();
    Vector3& operator=(const Vector3& other)
    {
        this->a[0]=other.a[0];
        this->a[1]=other.a[1];
        this->a[2]=other.a[2];
        return *this;
    };
    Vector3& operator+=(const Vector3& vec)
    {
        this->a[0]=this->a[0]+vec.a[0];
        this->a[1]=this->a[1]+vec.a[1];
        this->a[2]=this->a[2]+vec.a[2];
        return *this;
    };
    Vector3& operator-=(const Vector3& vec)
    {
        this->a[0]=this->a[0]-vec.a[0];
        this->a[1]=this->a[1]-vec.a[1];
        this->a[2]=this->a[2]-vec.a[2];
        return *this;
    };
    Vector3& operator*=(const Vector3& vec)
    {
        this->a[0]=this->a[0]*vec.a[0];
        this->a[1]=this->a[1]*vec.a[1];
        this->a[2]=this->a[2]*vec.a[2];
        return *this;
    };
    Vector3& operator/=(const Vector3& vec)
    {
        this->a[0]=this->a[0]/vec.a[0];
        this->a[1]=this->a[1]/vec.a[1];
        this->a[2]=this->a[2]/vec.a[2];
        return *this;
    };
    friend Vector3 operator+(Vector3 lhs, const Vector3& rhs)
    {
        return lhs+=rhs;
    }
    friend Vector3 operator-(Vector3 lhs, const Vector3& rhs)
    {
        return lhs-=rhs;
    }
    friend Vector3 operator*(Vector3 lhs, const Vector3& rhs)
    {
        return lhs*=rhs;
    }
    friend Vector3 operator/(Vector3 lhs, const Vector3& rhs)
    {
        return lhs/=rhs;
    }
    /*
    friend std::ostream& operator<<(std::ostream& out,Vector3 vec)
    {
        return out<<vec.a[0]<<" "<<vec.a[1]<<" "<<vec.a[2]<<std::endl;
    }
    */
    friend bool operator<(const Vector3& lhs,const Vector3& rhs)
    {
        if(lhs.a[0]>rhs.a[0]&&lhs.a[1]>rhs.a[1]&&lhs.a[2]>rhs.a[2]) return true;
        else return false;
    }
    friend bool operator>(const Vector3& lhs,const Vector3& rhs)
    {
        return rhs<lhs;
    }
    friend bool operator<=(const Vector3& lhs,const Vector3& rhs)
    {
        return !(lhs>rhs);
    }
    friend bool operator>=(const Vector3& lhs,const Vector3& rhs)
    {
        return !(lhs<rhs);
    }
    friend bool operator==(const Vector3& lhs,const Vector3& rhs)
    {
        if(lhs.a[0]==rhs.a[0]&&lhs.a[1]==rhs.a[1]&&lhs.a[2]==rhs.a[2]) return true;
        else return false;
    }
    friend bool operator!=(const Vector3& lhs,const Vector3& rhs)
    {
        return !(lhs==rhs);
    }
    /*
    float__& operator[](std::size_t idx)
    {
        return a[idx];
    };
    */
    /*
    const float__& operator[](std::size_t idx)const
    {
        return a[idx];
    };
    */
    Vector3* operator=(const Vector3* other)
    {
        (*this)=(*other);
        return this;
    };
    Vector3* operator+=(const Vector3* vec)
    {
        (*this)+=(*vec);
        return this;
    };
    Vector3* operator-=(const Vector3* vec)
    {
        (*this)-=(*vec);
        return this;
    };
    Vector3* operator*=(const Vector3* vec)
    {
        (*this)*=(*vec);
        return this;
    };
    Vector3* operator/=(const Vector3* vec)
    {
        (*this)/=(*vec);
        return this;
    };
    /*
    friend std::ostream& operator<<(std::ostream& out,Vector3* vec)
    {
        return out<<(*vec).a[0]<<" "<<(*vec).a[1]<<" "<<(*vec).a[2]<<std::endl;
    }
    */
    /*
            friend Vector3* operator+(Vector3* lhs,const Vector3* rhs){return lhs+=rhs;}
            friend Vector3* operator-(Vector3* lhs,const Vector3* rhs){return lhs-=rhs;}
            friend Vector3* operator*(Vector3* lhs, const Vector3* rhs){return lhs*=rhs;}
            friend Vector3* operator/(Vector3* lhs, const Vector3* rhs){return lhs/=rhs;}
            friend bool operator<(const Vector3* lhs,const Vector3* rhs){return (*rhs)<(*lhs);}
            friend bool operator>(const Vector3* lhs,const Vector3* rhs){return rhs<lhs;}
            friend bool operator<=(const Vector3* lhs,const Vector3* rhs){return !(lhs)>rhs);}
            friend bool operator>=(const Vector3* lhs,const Vector3* rhs){return !(lhs)<rhs);}
            friend bool operator==(const Vector3* lhs,const Vector3* rhs){return (*rhs)==(*lhs);}
            friend bool operator!=(const Vector3* lhs,const Vector3* rhs){return !(lhs==rhs);}
    */
};
#endif
