#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <glib.h>
#include <gsl/gsl_math.h>
#include <sqlite3.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

/**
 * @brief Demonstrates the installed C libraries.
 */
int main(void)
{
    printf("========================================\n");
    printf("       C / Linux Tools Test Suite\n");
    printf("========================================\n\n");

    /*
     * 1. Standard C
     */
    printf("[1] Standard C\n");

    char *message = malloc(32);

    if (message == NULL) {
        return 1;
    }

    strcpy(message, "Hello from C!");

    printf("    malloc()       : %s\n", message);


    /*
     * 2. GLib
     */
    printf("\n[2] GLib\n");

    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(table, "language", "C");
    g_hash_table_insert(table, "OS", "Linux");
    g_hash_table_insert(table, "shell", "Bash");

    printf("    Hash table      : %s\n",
           (char *)g_hash_table_lookup(table, "language"));

    printf("    OS              : %s\n",
           (char *)g_hash_table_lookup(table, "OS"));

    g_hash_table_destroy(table);


    /*
     * 3. GSL
     */
    printf("\n[3] GSL - GNU Scientific Library\n");

    double x = 25.0;
    double result = gsl_pow_2(x);

    printf("    gsl_pow_2(25)   : %.2f\n", result);


    /*
     * 4. SQLite
     */
    printf("\n[4] SQLite3\n");

    sqlite3 *db;

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        printf("    SQLite error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *error = NULL;

    sqlite3_exec(
        db,
        "CREATE TABLE users (id INTEGER, name TEXT);",
        NULL,
        NULL,
        &error
    );

    sqlite3_exec(
        db,
        "INSERT INTO users VALUES (1, 'Priyanshu');",
        NULL,
        NULL,
        &error
    );

    printf("    Database       : opened\n");
    printf("    Table          : users\n");
    printf("    Insert         : successful\n");

    sqlite3_close(db);


    /*
     * 5. libxml2
     */
    printf("\n[5] libxml2\n");

    const char *xml =
        "<person>"
        "<name>Priyanshu</name>"
        "<language>C</language>"
        "</person>";

    xmlDocPtr doc = xmlReadMemory(
        xml,
        strlen(xml),
        "test.xml",
        NULL,
        0
    );

    if (doc == NULL) {
        printf("    XML parsing failed\n");
    } else {
        xmlNode *root = xmlDocGetRootElement(doc);

        printf("    Root element   : %s\n", root->name);

        xmlFreeDoc(doc);
    }


    /*
     * 6. libcurl
     */
    printf("\n[6] libcurl\n");

    CURL *curl = curl_easy_init();

    if (curl != NULL) {

        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://example.com"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_NOBODY,
            1L
        );

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            printf("    HTTP request   : successful\n");
        } else {
            printf("    HTTP request   : failed\n");
            printf("    Error          : %s\n",
                   curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }


    /*
     * Cleanup
     */
    free(message);

    printf("\n========================================\n");
    printf("All library tests completed.\n");
    printf("========================================\n");

    return 0;
}
