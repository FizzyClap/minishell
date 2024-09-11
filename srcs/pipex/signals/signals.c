/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:46:28 by gartan            #+#    #+#             */
/*   Updated: 2024/09/10 17:48:54 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

	//	ISIG	When any of the characters INTR, QUIT, SUSP, or DSUSP are
	//			received, generate the corresponding signal.

		// STRUCTURE DES TERMIOS: termios_p

	//	tcflag_t	c_iflag;		/* input modes */
	//	tcflag_t	c_oflag;		/* output modes */
	//	tcflag_t	c_cflag;		/* control modes */
	//	tcflag_t	c_lflag;		/* local modes */
	//	cc_t		c_cc[NCCS];	/* special characters */

	
	//	int tcgetattr(int fd, struct termios *termios_p);
	//	int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
	
