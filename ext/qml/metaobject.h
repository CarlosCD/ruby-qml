#pragma once

#include "rubyclassbase.h"
#include <QtCore/QMetaObject>
#include <QtCore/QVector>
#include <QtCore/QHash>
#include <QtCore/QObject>

namespace RubyQml {

class MetaObject : public RubyClassBase<MetaObject>
{
    friend class RubyClassBase<MetaObject>;
public:

    MetaObject();

    VALUE className() const;

    VALUE methodNames() const;
    VALUE isPublic(VALUE name) const;
    VALUE isProtected(VALUE name) const;
    VALUE isPrivate(VALUE name) const;
    VALUE isSignal(VALUE name) const;

    VALUE invokeMethod(VALUE object, VALUE methodName, VALUE args) const;
    VALUE connectSignal(VALUE object, VALUE signalName, VALUE proc) const;

    VALUE propertyNames() const;
    VALUE getProperty(VALUE object, VALUE name) const;
    VALUE setProperty(VALUE object, VALUE name, VALUE newValue) const;
    VALUE notifySignal(VALUE name) const;

    VALUE enumerators() const;

    VALUE superClass() const;

    VALUE isEqual(VALUE other) const;
    VALUE hash() const;

    void setMetaObject(const QMetaObject *metaObject);
    const QMetaObject *metaObject() const { return mMetaObject; }

    static VALUE createOrUpdate(const QMetaObject *qmetaobj);

private:

    void mark() {}
    static ClassBuilder buildClass();

    QList<int> findMethods(VALUE name) const;
    int findProperty(VALUE name) const;

    const QMetaObject *mMetaObject = nullptr;
    QMultiHash<ID, int> mMethodHash;
    QHash<ID, int> mPropertyHash;

    static VALUE metaObjectHash;
};


}