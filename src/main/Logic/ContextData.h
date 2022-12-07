/*
 * File:   contextdata.h
 * @author Lehmann
 * @date April 12, 2019
 */

#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

class ContextData{
private:
    int errorCounter = 0;
public:
    void incErrorCounter();
    void clearErrorcounter();
    void show();

    int conIDDis = 0;
};


#endif /* CONTEXTDATA_H */
