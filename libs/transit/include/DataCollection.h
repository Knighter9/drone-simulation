#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

/**
 * @brief this class is responsible for collecting the data
 */
class DataCollection {
    public:
    // TODO: What do I need to add here to make this work?
    // Create an object of DataCollection?

    DataCollection() {
    // TODO: Should I initialize the variables here so that the object gets updated with the simulation?
    startTime = 0.0;
    endTime = 0.0;
    strategyUsed = "";

    }
    ~DataCollection();

    protected:
    
    double startTime;
    double endTime;
    std::string strategyUsed;
};



