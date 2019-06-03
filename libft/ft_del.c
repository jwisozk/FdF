#include "libft.h"

void	ft_del(void *s, size_t n)
{
    free(s);
    (void)n;
}
