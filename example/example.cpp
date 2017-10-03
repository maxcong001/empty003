
#include "logger/logger.hpp"
#include "bpnn/bpnn.hpp"

int main()
{
    set_log_level(logger_iface::log_level::debug);
    __LOG(error, "hello logger!"
                     << "this is error log");
    __LOG(warn, "hello logger!"
                    << "this is warn log");
    __LOG(info, "hello logger!"
                    << "this is info log");
    __LOG(debug, "hello logger!"
                     << "this is debug log");
#if 0
    //输入样本
    double X[trainsample][innode] = {{0, 0, 6, 1}, {0, 0, 2000, 1}, {1, 0, 1, 4}, {1, 2, 0, 1}, {1, 0, 2, 0}, {0, 0, 1, 5}, {1, 0, 1, 0}, {1, 0, 1, 1}};
    //期望输出样本
    double Y[trainsample][outnode] = {
        {0}, {0.1}, {0.2}, {0.3}, {0.4}, {0.25}, {0.15}, {0.19}};

    BpNet bp;
    bp.init();
    int times = 0;
    while (bp.error > 0.00007)
    {
        bp.e = 0.0;
        times++;
        bp.train(X, Y);
        cout << "Times=" << times << " error=" << bp.error << endl;
    }
    bp.writetrain();
    cout << "trainning complete..." << endl;
    double m[innode] = {1, 0, 1, 4};
    double *r = bp.recognize(m);
    for (int i = 0; i < outnode; ++i)
        cout << bp.result[i] << " \nMax: \n";
    double cha[trainsample][outnode];
    double mi = 100;
    double index;
    for (int i = 0; i < trainsample; i++)
    {
        for (int j = 0; j < outnode; j++)
        {
            //找差值最小的那个样本
            cha[i][j] = (double)(fabs(Y[i][j] - bp.result[j]));
            if (cha[i][j] < mi)
            {
                mi = cha[i][j];
                index = i;
            }
        }
    }
    for (int i = 0; i < innode; ++i)
        cout << m[i];
    cout << " is " << index << endl;
    cout << endl;
#endif
    return 0;
}
