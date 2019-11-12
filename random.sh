# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    random.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 18:11:33 by cbretagn          #+#    #+#              #
#    Updated: 2019/11/12 14:51:40 by cbretagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

for i in `seq 0 400`;
do
{
	VAR=`cat /dev/urandom | env LC_CTYPE=C tr -dc 'a-zA-Z0-9_' | fold -w 4 | head -n 1`
	echo $VAR;
}
done