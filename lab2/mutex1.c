#include <stdio.h>
#include <pthread.h>

int g_var1=0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
void *inc_gv()
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex1);
		g_var1++;
		for(j = 0; j < 5000000;j++);
		printf("%d ", g_var1);
		fflush(stdout);
		pthread_mutex_unlock(&mutex1);
	}
}

int main()
{
	pthread_t TA, TB;
	int TAret, TBret;
	TAret = pthread_create(&TA, NULL, inc_gv, NULL);
	TBret = pthread_create(&TA, NULL, inc_gv, NULL);

	pthread_join(TA, NULL);
	pthread_join(TB, NULL);
	printf("\nTA returned %d, TB returned %d, \npthread2 completed execution\n", TAret, TBret);
	return 0;
}

