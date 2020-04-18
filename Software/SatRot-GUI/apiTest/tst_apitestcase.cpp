#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "../GUI-Main/includes/api.h"

/**
 * @brief
 *
 */
class apiTestCase : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     */
    apiTestCase();
    /**
     * @brief
     *
     */
    ~apiTestCase();

private slots:
    /**
     * @brief
     *
     */
    void initTestCase();
    /**
     * @brief
     *
     */
    void cleanupTestCase();
    /**
     * @brief
     *
     */
    void test_case1();
    /**
     * @brief
     *
     */
    void test_case2();
    /**
     * @brief
     *
     */
    void test_case3();
    /**
     * @brief
     *
     */
    void test_case4();
    /**
     * @brief
     *
     */
    void test_case5();

private:
    int a; /**< TODO: describe */
    QString b, c, d, e; /**< TODO: describe */
    api* r = new api(this); /**< TODO: describe */
};

/**
 * @brief
 *
 */
apiTestCase::apiTestCase()
{
    QString url = "jsonplaceholder.typicode.com/users/3";
    r->initRequester(url, 80, nullptr);


    api::handleFunc getData = [this](const QJsonObject & o)
    {
        a = o.value("id").toInt();
        b = o.value("company")["name"].toString();
        c = o.value("address")["geo"]["lat"].toString();
        d = o.value("company")["catchPhrase"].toString();
    };

    api::handleFunc errData = [this](const QJsonObject & o)
    {
        e = "Error: connection dropped";
    };

    r->sendRequest(url, getData, errData);
    QTest::qWait(100);
}

/**
 * @brief
 *
 */
apiTestCase::~apiTestCase()
{
    delete r;
}

/**
 * @brief
 *
 */
void apiTestCase::initTestCase()
{

}

/**
 * @brief
 *
 */
void apiTestCase::cleanupTestCase()
{
    //delete r;
}

/**
 * @brief
 *
 */
void apiTestCase::test_case1()
{
    QCOMPARE(a, 3);
}

/**
 * @brief
 *
 */
void apiTestCase::test_case2()
{
    QCOMPARE(b, "Romaguera-Jacobson");
}

/**
 * @brief
 *
 */
void apiTestCase::test_case3()
{
    QCOMPARE(c, "-68.6102");
}

/**
 * @brief
 *
 */
void apiTestCase::test_case4()
{
    QCOMPARE(d, "Face to face bifurcated interface");
}

/**
 * @brief
 *Test error case with the wrong end point. this is to test what happens when a request fails
 */
void apiTestCase::test_case5()
{
    api* z = new api(this);
    QString url = "www.Rjsonplaceholder.typicode.com/users/3";
    z->initRequester(url, 80, nullptr);


    api::handleFunc getData = [this](const QJsonObject & o)
    {

    };

    api::handleFunc errData = [this](const QJsonObject & o)
    {
        e = "Error: connection dropped";
    };

    z->sendRequest(url, getData, errData);
    QTest::qWait(15);

    QCOMPARE(e, "Error: connection dropped");
}


QTEST_MAIN(apiTestCase)

#include "tst_apitestcase.moc"
