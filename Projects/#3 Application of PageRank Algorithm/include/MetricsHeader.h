#ifndef PROYECTO_METRICSHEADER_H
#define PROYECTO_METRICSHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include "NumberNameEquivalenceHeader.h"

// Global variables:
#define MAX_AMOUNT_METRICS 8

// Struct to store the metric:
typedef struct {
    const char *metric;
    double value;
} Metric;

typedef struct {
    Metric *metrics[MAX_AMOUNT_METRICS];
    char *fileName;
} MetricsPaper;

// Methods of the MetricsPaper struct:
MetricsPaper *createMetricsPaper(const char *filename);
void  printMetricsPaper(MetricsPaper *metricsPaper);
void addMetricsPaper(MetricsPaper *metricsPaper, const char *metric, double value);
double getMetricValue(Metric *metric);
const char *getMetricName(Metric *metric);
void freeMetricsPaper(MetricsPaper *metricsPaper);

#endif
