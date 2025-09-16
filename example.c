#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <rmn.h>
#include <rmn_build_info.h>

void printUsage(char **argv) {
    printf("librmn client example program that lists the fields in a file and the grid coordinates\n\n");
    printf("Usage:\n");
    printf("%s <fst file path>\n", argv[0]);
}


int main(int argc, char **argv) {
    rmn_print_build_info();

    printf("\n\n");

    if (argc != 2) {
        printUsage(argv);
        return 1;
    }
    char *filePath = argv[1];

    // Set library verbosity level
    c_fstopc("MSGLVL", "ERRORS", 0);

    // Get all values as 32bits at most.  If you want full field
    // precision, you need to consider the data type and allocate the
    // corresponding amount of memory
    c_fstopl("REDUCTION32", 1, 0);

    // Link file to a unit number (Fortran compatible I/O handle)
    int unitNb = 0;
    int resultCode = c_fnom(&unitNb, filePath, "STD+OLD+R/O", 0);
    if (resultCode < 0) {
        printf("Failed to link file %s !\n", filePath);
        return 1;
    }

    // Open the file
    resultCode = c_fstouv(unitNb, "RND");
    if (resultCode < 0) {
        printf("Failed to open the file %s !\n", filePath);
        return 1;
    }

    int recordNb = c_fstnbr(unitNb);
    printf("There are %d records in %s\n", recordNb, filePath);

    // Dimension along X
    uint32_t ni;
    // Dimension along Y
    uint32_t nj;
    // Dimension along Z
    uint32_t nk;
    // Forecast origin date
    uint32_t dateo;
    // Forecast timestep in seconds
    uint32_t deet;
    // Number of forecast steps
    uint32_t npas;
    // Number of bits per field element
    uint32_t nbits;
    // Data type
    uint32_t datyp;
    // Vertical level
    uint32_t ip1;
    // Second field identifier.  Usually the forecast hour
    uint32_t ip2;
    // Third field identifier.  User defined
    uint32_t ip3;
    // Variable type
    char typvar[3] = {' ', ' ', '\0'};
    // Variable name
    char nomvar[5] = {' ', ' ', ' ', ' ', '\0'};
    // Label
    char etiket[13] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
    // Grid type (geographical projection)
    char grtyp[2] = {' ', '\0'};
    // First grid descriptor
    uint32_t ig1;
    // Second grid descriptor
    uint32_t ig2;
    // Third grid descriptor
    uint32_t ig3;
    // Fourth grid descriptor
    uint32_t ig4;
    // ???
    uint32_t swa;
    // Header length (in 64 bits units)
    uint32_t lng;
    // ???
    uint32_t dltf;
    // ???
    uint32_t ubc;
    // ???
    uint32_t extra1, extra2, extra3;

    float lat = 0;
    float lon = 0;

    printf("nomvar\ttypvar\tgrtyp\tni\tnj\tnk\tip1\tip2\tip3\tetiket\tig1\tig2\tig3\tig4\n");

    // This function searches for field in the file.  An empty string for
    // string params and -1 for integers means everything
    int32_t key = c_fstinf(unitNb, &ni, &nj, &nk, -1, "", -1, -1, -1, "", "");
    do {
        printf("\tkey=%d\n", key);

        c_fstprm (key, &dateo, &deet, &npas, &ni, &nj, &nk, &nbits, &datyp, &ip1, &ip2, &ip3, typvar, nomvar, etiket, grtyp, &ig1, &ig2, &ig3, &ig4, &swa, &lng, &dltf, &ubc, &extra1, &extra2, &extra3);

        printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\n", nomvar, typvar, grtyp, ni, nj, nk, ip1, ip2, ip3, etiket, ig1, ig2, ig3, ig4);

        // Allocate memory to hold the field's data
        int32_t *field = malloc(ni * nj * nk * sizeof(int32_t));

        resultCode = c_fstluk(field, key, &ni, &nj, &nk);
        if (resultCode < 0) {
            printf("Failed to read the field!\n");
            return 1;
        }

        // A very simple that computes the average value of the field
        double sum = 0;
        for(int32_t i = 0; i < ni * nj * nk; i++) {
            // We don't bother with the organization of the elements within
            // the array since we want to access all the elements, but
            // if we wanted to access columns and rows, we have to consider
            // that the data is organized in column-major instead of row-major
            sum += field[i];
        }
        // Please note that this example does not take missing values into account
        printf("\tAverage value = %f\n", sum / (ni * nj * nk) );

        // Load grid definition
        int gridId = c_ezqkdef(ni, nj, grtyp, ig1, ig2, ig3, ig4, unitNb);

        // Print the lat/lon coordinates of each gridpoint
        for (int32_t i = 0; i < ni; i++) {
            for (int32_t j = 0; j < nj; j++) {
                // Get the lat/lon coordinates of a given grid point
                float iFloat = i;
                float jFloat = j;

                // This function expects 1 <= x <= NI and 1 <= y <= NJ
                // c_gdllfxy can retreive arrays of coordinates; the last
                // parameter is the number of points in the arrays.
                c_gdllfxy(gridId, &lat, &lon, &iFloat, &jFloat, 1);

                // Fix longitude to display it in a conventional way
                if (lon > 180) lon -= 360;

                printf("\t\t[%04d,%04d] = %03.5f, %03.5f\n", i, j, lat, lon);
            }
        }

        // Free grid definition
        c_gdrls(gridId);

        free(field);

        key = c_fstinfx(key, unitNb, &ni, &nj, &nk, -1, "", -1, -1, -1, "", "");
    } while (key > 0);

    // Close the file
    c_fstfrm(unitNb);

    return 0;
}
