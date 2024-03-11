#include "../include/MetricsHeader.h"

// Initialize the metrics of the papers from the  file with the format:
MetricsPaper *createMetricsPaper(const char *filename) {
    MetricsPaper *metricsPaper = (MetricsPaper *) malloc(sizeof(MetricsPaper));
    metricsPaper->fileName = (char *) malloc(strlen(filename) + 1);
    strcpy(metricsPaper->fileName, filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    char line[MAX_LINE_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (i == 0) {
            i++;
            continue;
        }
        char *token = strtok(line, ",");
        metricsPaper->metrics[i - 1] = (Metric *) malloc(sizeof(Metric));
        metricsPaper->metrics[i - 1]->metric = (char *) malloc(strlen(token) + 1);
        strcpy(metricsPaper->metrics[i - 1]->metric, token);
        token = strtok(NULL, ",");
        metricsPaper->metrics[i - 1]->value = strtod(token, NULL);
        i++;
    }
    fclose(file);
    return metricsPaper;
}

// Get the value of the metric:
double getMetricValue(Metric *metric) {
    return metric->value;
}

// Get the name of the metric:
const char *getMetricName(Metric *metric) {
    return metric->metric;
}

// Print the list of the metrics of the papers:
void printMetricsPaper(MetricsPaper *metricsPaper) {
printf("Metrics of the papers:\n");
    printf("File: %s\n", metricsPaper->fileName);
    for (int i = 0; i < MAX_AMOUNT_METRICS; i++) {
        printf("%s: %f\n", metricsPaper->metrics[i]->metric, metricsPaper->metrics[i]->value);
    }
}

// Free the memory of the metrics of the papers:
void freeMetricsPaper(MetricsPaper *metricsPaper) {
    free(metricsPaper->fileName);
    for (int i = 0; i < MAX_AMOUNT_METRICS; i++) {
        free(metricsPaper->metrics[i]);
    }
    free(metricsPaper);
}