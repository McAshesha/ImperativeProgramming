#include <stdio.h>
#include <stdlib.h>

//TODO: не работает на первом же тесте

typedef struct {
    long double start;
    long double end;
} Interval;

int compareIntervals(const void* a, const void* b) {
    Interval* ia = (Interval*)a;
    Interval* ib = (Interval*)b;
    if (ia->start < ib->start) return -1;
    if (ia->start > ib->start) return 1;
    return 0;
}

#define MAX_N 200000

long long N;
long double W, L;

Interval occupied[MAX_N];
long double positions[MAX_N];
long long totalFlies;

void simulateSeating(long long initialFlies) {
    totalFlies = initialFlies;
    long long occupiedCount = initialFlies;

    // Sort the occupied intervals
    qsort(occupied, occupiedCount, sizeof(Interval), compareIntervals);

    // Initialize free intervals
    Interval freeIntervals[MAX_N];
    long long freeCount = 0;

    // Add initial free interval before the first occupied interval
    if (occupied[0].start > 0.0L) {
        freeIntervals[freeCount++] = (Interval){0.0L, occupied[0].start};
    }

    // Find free intervals between occupied intervals
    for (long long i = 1; i < occupiedCount; i++) {
        if (occupied[i - 1].end < occupied[i].start) {
            freeIntervals[freeCount++] = (Interval){occupied[i - 1].end, occupied[i].start};
        }
    }

    // Add free interval after the last occupied interval
    if (occupied[occupiedCount - 1].end < L) {
        freeIntervals[freeCount++] = (Interval){occupied[occupiedCount - 1].end, L};
    }

    // Simulate the seating process
    int changed;
    do {
        changed = 0;

        // Find the free interval with the maximum minimal distance
        long double maxDist = -1.0L;
        long long bestIntervalIndex = -1;
        long double bestPosition = -1.0L;

        for (long long i = 0; i < freeCount; i++) {
            long double freeStart = freeIntervals[i].start;
            long double freeEnd = freeIntervals[i].end;
            long double freeLength = freeEnd - freeStart;

            if (freeLength < W) {
                continue;
            }

            long double candidatePosition = (freeStart + freeEnd) / 2.0L;
            // Adjust candidate position if necessary
            if (candidatePosition - W / 2.0L < freeStart) {
                candidatePosition = freeStart + W / 2.0L;
            } else if (candidatePosition + W / 2.0L > freeEnd) {
                candidatePosition = freeEnd - W / 2.0L;
            }

            // Calculate minimal distance to occupied intervals and ends
            long double leftDist = candidatePosition - W / 2.0L - freeStart;
            long double rightDist = freeEnd - candidatePosition - W / 2.0L;
            long double minDist = leftDist < rightDist ? leftDist : rightDist;

            if (minDist > maxDist || (minDist == maxDist && candidatePosition < bestPosition)) {
                maxDist = minDist;
                bestIntervalIndex = i;
                bestPosition = candidatePosition;
            }
        }

        if (bestIntervalIndex != -1) {
            // Place the new fly
            positions[totalFlies++] = bestPosition;
            Interval newOccupied = {bestPosition - W / 2.0L, bestPosition + W / 2.0L};

            // Update occupied intervals
            // Insert newOccupied into occupied[]
            long long insertPos = occupiedCount;
            for (long long i = 0; i < occupiedCount; i++) {
                if (newOccupied.start < occupied[i].start) {
                    insertPos = i;
                    break;
                }
            }
            // Shift intervals to make room
            for (long long i = occupiedCount; i > insertPos; i--) {
                occupied[i] = occupied[i - 1];
            }
            occupied[insertPos] = newOccupied;
            occupiedCount++;

            // Merge overlapping intervals
            long long i = insertPos;
            // Merge with previous intervals if necessary
            while (i > 0 && occupied[i - 1].end >= occupied[i].start) {
                occupied[i - 1].end = occupied[i].end > occupied[i - 1].end ? occupied[i].end : occupied[i - 1].end;
                // Remove occupied[i]
                for (long long j = i; j < occupiedCount - 1; j++) {
                    occupied[j] = occupied[j + 1];
                }
                occupiedCount--;
                i--;
            }
            // Merge with next intervals if necessary
            while (i < occupiedCount - 1 && occupied[i].end >= occupied[i + 1].start) {
                occupied[i].end = occupied[i + 1].end > occupied[i].end ? occupied[i + 1].end : occupied[i].end;
                // Remove occupied[i + 1]
                for (long long j = i + 1; j < occupiedCount - 1; j++) {
                    occupied[j] = occupied[j + 1];
                }
                occupiedCount--;
            }

            // Recompute free intervals
            freeCount = 0;
            if (occupied[0].start > 0.0L) {
                freeIntervals[freeCount++] = (Interval){0.0L, occupied[0].start};
            }
            for (long long i = 1; i < occupiedCount; i++) {
                if (occupied[i - 1].end < occupied[i].start) {
                    freeIntervals[freeCount++] = (Interval){occupied[i - 1].end, occupied[i].start};
                }
            }
            if (occupied[occupiedCount - 1].end < L) {
                freeIntervals[freeCount++] = (Interval){occupied[occupiedCount - 1].end, L};
            }

            changed = 1;
        }
    } while (changed);
}

int main() {
    scanf("%lld %Lf", &N, &W);
    scanf("%Lf", &L);

    // Arrays to store initial positions for minimal and maximal cases
    long double minPositions[N];
    long double maxPositions[N];

    // Minimal Case
    {
        // Compute minimal gap
        long double G = (L - N * W) / (N + 1);
        for (long long i = 0; i < N; i++) {
            minPositions[i] = G * (i + 1) + W / 2.0L + W * i;
        }

        // Initialize occupied intervals
        for (long long i = 0; i < N; i++) {
            occupied[i].start = minPositions[i] - W / 2.0L;
            occupied[i].end = minPositions[i] + W / 2.0L;
            positions[i] = minPositions[i];
        }

        // Simulate seating
        simulateSeating(N);

        long long minTotalFlies = totalFlies;

        // Output minimal case
        printf("%lld ", minTotalFlies);
        // We'll compute maxTotalFlies later
    }

    // Maximal Case
    {
        // Compute positions to maximize free intervals
        if (N == 1) {
            maxPositions[0] = L / 2.0L;
        } else {
            // Place the first fly at W/2 + margin
            long double margin = W; // Can adjust margin as needed
            long double firstPos = W / 2.0L + margin;
            long double lastPos = L - W / 2.0L;
            long double s = (lastPos - firstPos) / (N - 1);

            for (long long i = 0; i < N; i++) {
                maxPositions[i] = firstPos + i * s;
                if (maxPositions[i] - W / 2.0L < 0.0L) {
                    maxPositions[i] = W / 2.0L;
                }
                if (maxPositions[i] + W / 2.0L > L) {
                    maxPositions[i] = L - W / 2.0L;
                }
            }
        }

        // Initialize occupied intervals
        for (long long i = 0; i < N; i++) {
            occupied[i].start = maxPositions[i] - W / 2.0L;
            occupied[i].end = maxPositions[i] + W / 2.0L;
            positions[i] = maxPositions[i];
        }

        // Simulate seating
        simulateSeating(N);

        long long maxTotalFlies = totalFlies;

        // Now output the results

        // From earlier minimal case
        printf("%lld\n", maxTotalFlies);

        // Output minimal positions
        for (long long i = 0; i < N; i++) {
            printf("%.9Lf\n", minPositions[i]);
        }

        // Output maximal positions
        for (long long i = 0; i < N; i++) {
            printf("%.9Lf\n", maxPositions[i]);
        }
    }

    return 0;
}
