
void top_n_webpages(int num_webpages, int *num_involvements, int n) {
    int *top_n = calloc(n, sizeof(int));
    int *web_page_nr = calloc(n, sizeof(int));

    printf("num webpages: %i\n", num_webpages);
    printf("top n: %i\n", n);

    
    for (int i = 0; i < num_webpages ; i++) {
        printf("%i ", num_involvements[i]);
    }

    printf("\n");
    for (int i = 0; i < num_webpages; i++) {
        for (int j = 0; j < n; j++) {
            if (num_involvements[i] >= top_n[j]) {
                //Shuffling every value in top_n and web_page_nr
                //one index backward to make room for new larger value.
                for (int k = n - 1 ; k > j ; k--) {   
                    top_n[k] = top_n[k-1];
                    web_page_nr[k] = web_page_nr[k-1];
                }

                //Updating with new largest value.
                top_n[j] = num_involvements[i];
                web_page_nr[j] = i;
                break;
            }   
        }
    }
    for (int i = 0; i < n ; i++) {
        printf("Web page nr %i had %i involvements\n ", web_page_nr[i] + 1, top_n[i]);
    }
    free(top_n);
    free(web_page_nr);
}

void pragma_top_n_webpages(int num_webpages, int *num_involvements, int n) {
    int nr_threads = 2; //Temporary hardcoding for testing implementation.
    int pages_per_thread = num_webpages / nr_threads;
    int top_pages_per_thread = n / nr_threads;
    int *top_n = calloc(n*nr_threads, sizeof(int));
    int *web_page_nr = calloc(n*nr_threads, sizeof(int));
    int *top_n_short  = calloc(n, sizeof(int));
    int *web_page_nr_short = calloc(n,sizeof(int));

    printf("num webpages: %i\n", num_webpages);
    printf("top n: %i\n", n);


    
    #pragma omp parallel num_threads(nr_threads)
    {
    int thread_num = omp_get_thread_num();
    // One thread has to do some extra work if number of webpages cannot be evenly split.
    if (thread_num == nr_threads - 1) {
        for (int i = pages_per_thread * (thread_num-1); i < num_webpages; i++) {
            for (int j = (nr_threads - 1) * n ; j < n * nr_threads; j++) {
                if (num_involvements[i] >= top_n[j]) {
                    // Shuffling every value in top_n and web_page_nr
                    // one index backward to make room for new larger value.
                    for (int k = n - 1 ; k > j ; k--) {   
                        top_n[k] = top_n[k-1];
                        web_page_nr[k] = web_page_nr[k-1];
                    }

                    // Updating with new largest value.
                    top_n[j] = num_involvements[i];
                    web_page_nr[j] = i;
                    break;
                }   
            }
        }
        
    }
    else {
        for (int i = thread_num * pages_per_thread; i < (thread_num + 1) * pages_per_thread; i++) {
            for (int j = thread_num * top_pages_per_thread; j < thread_num * top_pages_per_thread; j++) {
                if (num_involvements[i] >= top_n[j]) {
                    // Shuffling every value in top_n and web_page_nr
                    // one index backward to make room for new larger value.
                    for (int k = n - 1 ; k > j ; k--) {   
                        top_n[k] = top_n[k-1];
                        web_page_nr[k] = web_page_nr[k-1];
                    }

                    // Updating with new largest value.
                    top_n[j] = num_involvements[i];
                    web_page_nr[j] = i;
                    break;
                }
            }
        }
    }
    }
    for (int i = 0; i < n * nr_threads ; i++) {
        printf("Web page nr %i had %i involvements\n ", web_page_nr[i] + 1, top_n[i]);
    }
    printf("parallel part finished\n");
    for (int i = 0; i < num_webpages; i++) {
        for (int j = 0; j < n*nr_threads; j++) {
            if (num_involvements[i] >= top_n[j]) {
                //Shuffling every value in top_n and web_page_nr
                //one index backward to make room for new larger value.
                for (int k = n - 1 ; k > j ; k--) {   
                    top_n[k] = top_n[k-1];
                }

                //Updating with new largest value.
                top_n[j] = num_involvements[i];
                web_page_nr[j] = i;
                break;
            }   
        }
    }


    for (int i = 0; i < n ; i++) {
        printf("Web page nr %i had %i involvements\n ", web_page_nr[i] + 1, top_n[i]);
    }
    free(top_n);
    free(web_page_nr);
}