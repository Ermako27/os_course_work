#ifndef __COMM_H__
#define __COMM_H__

#include <linux/skbuff.h>

struct comm_nl {
	pid_t user_pid;
	struct sock * nl_sock;
};

#define NETLINK_EXECMON (31) /* Last possible netlink */

int 	COMM_nl_send_exec_msg(char * exec_str);
int	COMM_nl_init(void);
int 	COMM_nl_destruct(void);
void	COMM_nl_input(struct sk_buff * skb);

#endif /* __COMM_H__ */



