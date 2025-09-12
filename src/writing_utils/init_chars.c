/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmanique <gmanique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:44:00 by gmanique          #+#    #+#             */
/*   Updated: 2025/09/12 10:26:05 by gmanique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_term.h"

static void	init_unprintable(char (*digit)[5][5])
{
	int	i;

	i = 0;
	while(!ft_isprint(i))
	{
		ft_strlcpy(digit[i][0], "00000", 6);
		ft_strlcpy(digit[i][1], "00000", 6);
		ft_strlcpy(digit[i][2], "00000", 6);
		ft_strlcpy(digit[i][3], "00000", 6);
		ft_strlcpy(digit[i][4], "00000", 6);
		i++;
	}
}

/* L'enfer putain. */
void	init_chars(char (*digit)[5][5])
{
	init_unprintable(digit);
	
	ft_strlcpy(digit[32][0], "00000", 6);
	ft_strlcpy(digit[32][1], "00000", 6);
	ft_strlcpy(digit[32][2], "00000", 6);
	ft_strlcpy(digit[32][3], "00000", 6);
	ft_strlcpy(digit[32][4], "00000", 6);

	ft_strlcpy(digit[33][0], "00100", 6);
	ft_strlcpy(digit[33][1], "00100", 6);
	ft_strlcpy(digit[33][2], "00100", 6);
	ft_strlcpy(digit[33][3], "00000", 6);
	ft_strlcpy(digit[33][4], "00100", 6);
	
	ft_strlcpy(digit[34][0], "01010", 6);
	ft_strlcpy(digit[34][1], "01010", 6);
	ft_strlcpy(digit[34][2], "00000", 6);
	ft_strlcpy(digit[34][3], "00000", 6);
	ft_strlcpy(digit[34][4], "00000", 6);

	ft_strlcpy(digit[35][0], "01010", 6);
	ft_strlcpy(digit[35][1], "11111", 6);
	ft_strlcpy(digit[35][2], "01010", 6);
	ft_strlcpy(digit[35][3], "11111", 6);
	ft_strlcpy(digit[35][4], "01010", 6);

	ft_strlcpy(digit[36][0], "01110", 6);
	ft_strlcpy(digit[36][1], "10100", 6);
	ft_strlcpy(digit[36][2], "01110", 6);
	ft_strlcpy(digit[36][3], "00101", 6);
	ft_strlcpy(digit[36][4], "01110", 6);

	ft_strlcpy(digit[37][0], "10001", 6);
	ft_strlcpy(digit[37][1], "00010", 6);
	ft_strlcpy(digit[37][2], "00100", 6);
	ft_strlcpy(digit[37][3], "01000", 6);
	ft_strlcpy(digit[37][4], "10001", 6);
	
	ft_strlcpy(digit[38][0], "01000", 6);
	ft_strlcpy(digit[38][1], "10101", 6);
	ft_strlcpy(digit[38][2], "01010", 6);
	ft_strlcpy(digit[38][3], "10100", 6);
	ft_strlcpy(digit[38][4], "01010", 6);

	ft_strlcpy(digit[39][0], "00100", 6);
	ft_strlcpy(digit[39][1], "00100", 6);
	ft_strlcpy(digit[39][2], "00000", 6);
	ft_strlcpy(digit[39][3], "00000", 6);
	ft_strlcpy(digit[39][4], "00000", 6);

	ft_strlcpy(digit[40][0], "00010", 6);
	ft_strlcpy(digit[40][1], "00100", 6);
	ft_strlcpy(digit[40][2], "00100", 6);
	ft_strlcpy(digit[40][3], "00100", 6);
	ft_strlcpy(digit[40][4], "00010", 6);
	
	ft_strlcpy(digit[41][0], "01000", 6);
	ft_strlcpy(digit[41][1], "00100", 6);
	ft_strlcpy(digit[41][2], "00100", 6);
	ft_strlcpy(digit[41][3], "00100", 6);
	ft_strlcpy(digit[41][4], "01000", 6);
	
	ft_strlcpy(digit[42][0], "01110", 6);
	ft_strlcpy(digit[42][1], "01110", 6);
	ft_strlcpy(digit[42][2], "01110", 6);
	ft_strlcpy(digit[42][3], "00000", 6);
	ft_strlcpy(digit[42][4], "00000", 6);
	
	ft_strlcpy(digit[43][0], "00000", 6);
	ft_strlcpy(digit[43][1], "00100", 6);
	ft_strlcpy(digit[43][2], "01110", 6);
	ft_strlcpy(digit[43][3], "00100", 6);
	ft_strlcpy(digit[43][4], "00000", 6);

	ft_strlcpy(digit[44][0], "00000", 6);
	ft_strlcpy(digit[44][1], "00000", 6);
	ft_strlcpy(digit[44][2], "00100", 6);
	ft_strlcpy(digit[44][3], "00100", 6);
	ft_strlcpy(digit[44][4], "01000", 6);

	ft_strlcpy(digit[45][0], "00000", 6);
	ft_strlcpy(digit[45][1], "00000", 6);
	ft_strlcpy(digit[45][2], "01110", 6);
	ft_strlcpy(digit[45][3], "00000", 6);
	ft_strlcpy(digit[45][4], "00000", 6);

	ft_strlcpy(digit[46][0], "00000", 6);
	ft_strlcpy(digit[46][1], "00000", 6);
	ft_strlcpy(digit[46][2], "00000", 6);
	ft_strlcpy(digit[46][3], "00000", 6);
	ft_strlcpy(digit[46][4], "00100", 6);

	ft_strlcpy(digit[47][0], "00001", 6);
	ft_strlcpy(digit[47][1], "00010", 6);
	ft_strlcpy(digit[47][2], "00100", 6);
	ft_strlcpy(digit[47][3], "01000", 6);
	ft_strlcpy(digit[47][4], "10000", 6);

	ft_strlcpy(digit[48][0], "01110", 6);
	ft_strlcpy(digit[48][1], "10011", 6);
	ft_strlcpy(digit[48][2], "10101", 6);
	ft_strlcpy(digit[48][3], "11001", 6);
	ft_strlcpy(digit[48][4], "01110", 6);

	ft_strlcpy(digit[49][0], "00100", 6);
	ft_strlcpy(digit[49][1], "01100", 6);
	ft_strlcpy(digit[49][2], "00100", 6);
	ft_strlcpy(digit[49][3], "00100", 6);
	ft_strlcpy(digit[49][4], "01110", 6);

	ft_strlcpy(digit[50][0], "01110", 6);
	ft_strlcpy(digit[50][1], "10001", 6);
	ft_strlcpy(digit[50][2], "00110", 6);
	ft_strlcpy(digit[50][3], "01000", 6);
	ft_strlcpy(digit[50][4], "11111", 6);

	ft_strlcpy(digit[51][0], "11110", 6);
	ft_strlcpy(digit[51][1], "00001", 6);
	ft_strlcpy(digit[51][2], "00110", 6);
	ft_strlcpy(digit[51][3], "00001", 6);
	ft_strlcpy(digit[51][4], "11110", 6);

	ft_strlcpy(digit[52][0], "10010", 6);
	ft_strlcpy(digit[52][1], "10010", 6);
	ft_strlcpy(digit[52][2], "11111", 6);
	ft_strlcpy(digit[52][3], "00010", 6);
	ft_strlcpy(digit[52][4], "00010", 6);

	ft_strlcpy(digit[53][0], "11111", 6);
	ft_strlcpy(digit[53][1], "10000", 6);
	ft_strlcpy(digit[53][2], "11110", 6);
	ft_strlcpy(digit[53][3], "00001", 6);
	ft_strlcpy(digit[53][4], "11110", 6);

	ft_strlcpy(digit[54][0], "01110", 6);
	ft_strlcpy(digit[54][1], "10000", 6);
	ft_strlcpy(digit[54][2], "11110", 6);
	ft_strlcpy(digit[54][3], "10001", 6);
	ft_strlcpy(digit[54][4], "01110", 6);

	ft_strlcpy(digit[55][0], "11111", 6);
	ft_strlcpy(digit[55][1], "00010", 6);
	ft_strlcpy(digit[55][2], "00100", 6);
	ft_strlcpy(digit[55][3], "01000", 6);
	ft_strlcpy(digit[55][4], "01000", 6);

	ft_strlcpy(digit[56][0], "01110", 6);
	ft_strlcpy(digit[56][1], "10001", 6);
	ft_strlcpy(digit[56][2], "01110", 6);
	ft_strlcpy(digit[56][3], "10001", 6);
	ft_strlcpy(digit[56][4], "01110", 6);

	ft_strlcpy(digit[57][0], "01110", 6);
	ft_strlcpy(digit[57][1], "10001", 6);
	ft_strlcpy(digit[57][2], "01111", 6);
	ft_strlcpy(digit[57][3], "00001", 6);
	ft_strlcpy(digit[57][4], "01110", 6);

	ft_strlcpy(digit[58][0], "00000", 6);
	ft_strlcpy(digit[58][1], "00100", 6);
	ft_strlcpy(digit[58][2], "00000", 6);
	ft_strlcpy(digit[58][3], "00100", 6);
	ft_strlcpy(digit[58][4], "00000", 6);

	ft_strlcpy(digit[59][0], "00000", 6);
	ft_strlcpy(digit[59][1], "00100", 6);
	ft_strlcpy(digit[59][2], "00000", 6);
	ft_strlcpy(digit[59][3], "00100", 6);
	ft_strlcpy(digit[59][4], "01000", 6);

	ft_strlcpy(digit[60][0], "00010", 6);
	ft_strlcpy(digit[60][1], "00100", 6);
	ft_strlcpy(digit[60][2], "01000", 6);
	ft_strlcpy(digit[60][3], "00100", 6);
	ft_strlcpy(digit[60][4], "00010", 6);

	ft_strlcpy(digit[61][0], "00000", 6);
	ft_strlcpy(digit[61][1], "11111", 6);
	ft_strlcpy(digit[61][2], "00000", 6);
	ft_strlcpy(digit[61][3], "11111", 6);
	ft_strlcpy(digit[61][4], "00000", 6);

	ft_strlcpy(digit[62][0], "01000", 6);
	ft_strlcpy(digit[62][1], "00100", 6);
	ft_strlcpy(digit[62][2], "00010", 6);
	ft_strlcpy(digit[62][3], "00100", 6);
	ft_strlcpy(digit[62][4], "01000", 6);

	ft_strlcpy(digit[63][0], "01110", 6);
	ft_strlcpy(digit[63][1], "10001", 6);
	ft_strlcpy(digit[63][2], "00010", 6);
	ft_strlcpy(digit[63][3], "00000", 6);
	ft_strlcpy(digit[63][4], "00100", 6);

	ft_strlcpy(digit[64][0], "01110", 6);
	ft_strlcpy(digit[64][1], "10001", 6);
	ft_strlcpy(digit[64][2], "01101", 6);
	ft_strlcpy(digit[64][3], "10111", 6);
	ft_strlcpy(digit[64][4], "01110", 6);
	
	ft_strlcpy(digit[65][0], "01110", 6);
	ft_strlcpy(digit[65][1], "10001", 6);
	ft_strlcpy(digit[65][2], "11111", 6);
	ft_strlcpy(digit[65][3], "10001", 6);
	ft_strlcpy(digit[65][4], "10001", 6);
	
	ft_strlcpy(digit[66][0], "11110", 6);
	ft_strlcpy(digit[66][1], "10001", 6);
	ft_strlcpy(digit[66][2], "11110", 6);
	ft_strlcpy(digit[66][3], "10001", 6);
	ft_strlcpy(digit[66][4], "11110", 6);

	ft_strlcpy(digit[67][0], "01111", 6);
	ft_strlcpy(digit[67][1], "10000", 6);
	ft_strlcpy(digit[67][2], "10000", 6);
	ft_strlcpy(digit[67][3], "10000", 6);
	ft_strlcpy(digit[67][4], "01111", 6);

	ft_strlcpy(digit[68][0], "11110", 6);
	ft_strlcpy(digit[68][1], "10001", 6);
	ft_strlcpy(digit[68][2], "10001", 6);
	ft_strlcpy(digit[68][3], "10001", 6);
	ft_strlcpy(digit[68][4], "11110", 6);

	ft_strlcpy(digit[69][0], "11111", 6);
	ft_strlcpy(digit[69][1], "10000", 6);
	ft_strlcpy(digit[69][2], "11111", 6);
	ft_strlcpy(digit[69][3], "10000", 6);
	ft_strlcpy(digit[69][4], "11111", 6);

	ft_strlcpy(digit[70][0], "11111", 6);
	ft_strlcpy(digit[70][1], "10000", 6);
	ft_strlcpy(digit[70][2], "11111", 6);
	ft_strlcpy(digit[70][3], "10000", 6);
	ft_strlcpy(digit[70][4], "10000", 6);

	ft_strlcpy(digit[71][0], "01110", 6);
	ft_strlcpy(digit[71][1], "10000", 6);
	ft_strlcpy(digit[71][2], "10010", 6);
	ft_strlcpy(digit[71][3], "10001", 6);
	ft_strlcpy(digit[71][4], "01110", 6);

	ft_strlcpy(digit[72][0], "10001", 6);
	ft_strlcpy(digit[72][1], "10001", 6);
	ft_strlcpy(digit[72][2], "11111", 6);
	ft_strlcpy(digit[72][3], "10001", 6);
	ft_strlcpy(digit[72][4], "10001", 6);

	ft_strlcpy(digit[73][0], "11111", 6);
	ft_strlcpy(digit[73][1], "00100", 6);
	ft_strlcpy(digit[73][2], "00100", 6);
	ft_strlcpy(digit[73][3], "00100", 6);
	ft_strlcpy(digit[73][4], "11111", 6);

	ft_strlcpy(digit[74][0], "11111", 6);
	ft_strlcpy(digit[74][1], "00010", 6);
	ft_strlcpy(digit[74][2], "00010", 6);
	ft_strlcpy(digit[74][3], "10010", 6);
	ft_strlcpy(digit[74][4], "01100", 6);

	ft_strlcpy(digit[75][0], "10010", 6);
	ft_strlcpy(digit[75][1], "10100", 6);
	ft_strlcpy(digit[75][2], "11000", 6);
	ft_strlcpy(digit[75][3], "10100", 6);
	ft_strlcpy(digit[75][4], "10010", 6);

	ft_strlcpy(digit[76][0], "10000", 6);
	ft_strlcpy(digit[76][1], "10000", 6);
	ft_strlcpy(digit[76][2], "10000", 6);
	ft_strlcpy(digit[76][3], "10000", 6);
	ft_strlcpy(digit[76][4], "11110", 6);

	ft_strlcpy(digit[77][0], "10001", 6);
	ft_strlcpy(digit[77][1], "11011", 6);
	ft_strlcpy(digit[77][2], "10101", 6);
	ft_strlcpy(digit[77][3], "10001", 6);
	ft_strlcpy(digit[77][4], "10001", 6);

	ft_strlcpy(digit[78][0], "10001", 6);
	ft_strlcpy(digit[78][1], "11001", 6);
	ft_strlcpy(digit[78][2], "10101", 6);
	ft_strlcpy(digit[78][3], "10011", 6);
	ft_strlcpy(digit[78][4], "10001", 6);

	ft_strlcpy(digit[79][0], "01110", 6);
	ft_strlcpy(digit[79][1], "10001", 6);
	ft_strlcpy(digit[79][2], "10001", 6);
	ft_strlcpy(digit[79][3], "10001", 6);
	ft_strlcpy(digit[79][4], "01110", 6);

	ft_strlcpy(digit[80][0], "01110", 6);
	ft_strlcpy(digit[80][1], "10001", 6);
	ft_strlcpy(digit[80][2], "11110", 6);
	ft_strlcpy(digit[80][3], "10000", 6);
	ft_strlcpy(digit[80][4], "10000", 6);

	ft_strlcpy(digit[81][0], "01110", 6);
	ft_strlcpy(digit[81][1], "10001", 6);
	ft_strlcpy(digit[81][2], "10101", 6);
	ft_strlcpy(digit[81][3], "10010", 6);
	ft_strlcpy(digit[81][4], "01101", 6);

	ft_strlcpy(digit[82][0], "11110", 6);
	ft_strlcpy(digit[82][1], "10001", 6);
	ft_strlcpy(digit[82][2], "11110", 6);
	ft_strlcpy(digit[82][3], "10100", 6);
	ft_strlcpy(digit[82][4], "10010", 6);

	ft_strlcpy(digit[83][0], "01110", 6);
	ft_strlcpy(digit[83][1], "10000", 6);
	ft_strlcpy(digit[83][2], "01110", 6);
	ft_strlcpy(digit[83][3], "00001", 6);
	ft_strlcpy(digit[83][4], "01110", 6);

	ft_strlcpy(digit[84][0], "11111", 6);
	ft_strlcpy(digit[84][1], "00100", 6);
	ft_strlcpy(digit[84][2], "00100", 6);
	ft_strlcpy(digit[84][3], "00100", 6);
	ft_strlcpy(digit[84][4], "00100", 6);

	ft_strlcpy(digit[85][0], "10001", 6);
	ft_strlcpy(digit[85][1], "10001", 6);
	ft_strlcpy(digit[85][2], "10001", 6);
	ft_strlcpy(digit[85][3], "10001", 6);
	ft_strlcpy(digit[85][4], "01110", 6);

	ft_strlcpy(digit[86][0], "10001", 6);
	ft_strlcpy(digit[86][1], "10001", 6);
	ft_strlcpy(digit[86][2], "01010", 6);
	ft_strlcpy(digit[86][3], "01010", 6);
	ft_strlcpy(digit[86][4], "00100", 6);

	ft_strlcpy(digit[87][0], "10001", 6);
	ft_strlcpy(digit[87][1], "10001", 6);
	ft_strlcpy(digit[87][2], "10101", 6);
	ft_strlcpy(digit[87][3], "11011", 6);
	ft_strlcpy(digit[87][4], "10001", 6);

	ft_strlcpy(digit[88][0], "10001", 6);
	ft_strlcpy(digit[88][1], "01010", 6);
	ft_strlcpy(digit[88][2], "00100", 6);
	ft_strlcpy(digit[88][3], "01010", 6);
	ft_strlcpy(digit[88][4], "10001", 6);

	ft_strlcpy(digit[89][0], "10001", 6);
	ft_strlcpy(digit[89][1], "01010", 6);
	ft_strlcpy(digit[89][2], "00100", 6);
	ft_strlcpy(digit[89][3], "00100", 6);
	ft_strlcpy(digit[89][4], "00100", 6);

	ft_strlcpy(digit[90][0], "11111", 6);
	ft_strlcpy(digit[90][1], "00010", 6);
	ft_strlcpy(digit[90][2], "00100", 6);
	ft_strlcpy(digit[90][3], "01000", 6);
	ft_strlcpy(digit[90][4], "11111", 6);

	ft_strlcpy(digit[91][0], "01110", 6);
	ft_strlcpy(digit[91][1], "01000", 6);
	ft_strlcpy(digit[91][2], "01000", 6);
	ft_strlcpy(digit[91][3], "01000", 6);
	ft_strlcpy(digit[91][4], "01110", 6);

	ft_strlcpy(digit[92][0], "10000", 6);
	ft_strlcpy(digit[92][1], "01000", 6);
	ft_strlcpy(digit[92][2], "00100", 6);
	ft_strlcpy(digit[92][3], "00010", 6);
	ft_strlcpy(digit[92][4], "00001", 6);

	ft_strlcpy(digit[93][0], "01110", 6);
	ft_strlcpy(digit[93][1], "00010", 6);
	ft_strlcpy(digit[93][2], "00010", 6);
	ft_strlcpy(digit[93][3], "00010", 6);
	ft_strlcpy(digit[93][4], "01110", 6);

	ft_strlcpy(digit[94][0], "00100", 6);
	ft_strlcpy(digit[94][1], "01010", 6);
	ft_strlcpy(digit[94][2], "00000", 6);
	ft_strlcpy(digit[94][3], "00000", 6);
	ft_strlcpy(digit[94][4], "00000", 6);

	ft_strlcpy(digit[95][0], "00000", 6);
	ft_strlcpy(digit[95][1], "00000", 6);
	ft_strlcpy(digit[95][2], "00000", 6);
	ft_strlcpy(digit[95][3], "00000", 6);
	ft_strlcpy(digit[95][4], "11111", 6);

	ft_strlcpy(digit[96][0], "01000", 6);
	ft_strlcpy(digit[96][1], "00100", 6);
	ft_strlcpy(digit[96][2], "00000", 6);
	ft_strlcpy(digit[96][3], "00000", 6);
	ft_strlcpy(digit[96][4], "00000", 6);

	// ft_strlcpy(digit[97][0], "01110", 6);
	// ft_strlcpy(digit[97][1], "10001", 6);
	// ft_strlcpy(digit[97][2], "11111", 6);
	// ft_strlcpy(digit[97][3], "10001", 6);
	// ft_strlcpy(digit[97][4], "10001", 6);

	// ft_strlcpy(digit[98][0], "11110", 6);
	// ft_strlcpy(digit[98][1], "10001", 6);
	// ft_strlcpy(digit[98][2], "11110", 6);
	// ft_strlcpy(digit[98][3], "10001", 6);
	// ft_strlcpy(digit[98][4], "11110", 6);

	// ft_strlcpy(digit[99][0], "01111", 6);
	// ft_strlcpy(digit[99][1], "10000", 6);
	// ft_strlcpy(digit[99][2], "10000", 6);
	// ft_strlcpy(digit[99][3], "10000", 6);
	// ft_strlcpy(digit[99][4], "01111", 6);

	// ft_strlcpy(digit[100][0], "11110", 6);
	// ft_strlcpy(digit[100][1], "10001", 6);
	// ft_strlcpy(digit[100][2], "10001", 6);
	// ft_strlcpy(digit[100][3], "10001", 6);
	// ft_strlcpy(digit[100][4], "11110", 6);

	// ft_strlcpy(digit[101][0], "11111", 6);
	// ft_strlcpy(digit[101][1], "10000", 6);
	// ft_strlcpy(digit[101][2], "11111", 6);
	// ft_strlcpy(digit[101][3], "10000", 6);
	// ft_strlcpy(digit[101][4], "11111", 6);

	// ft_strlcpy(digit[102][0], "11111", 6);
	// ft_strlcpy(digit[102][1], "10000", 6);
	// ft_strlcpy(digit[102][2], "11111", 6);
	// ft_strlcpy(digit[102][3], "10000", 6);
	// ft_strlcpy(digit[102][4], "10000", 6);

	// ft_strlcpy(digit[103][0], "01110", 6);
	// ft_strlcpy(digit[103][1], "10000", 6);
	// ft_strlcpy(digit[103][2], "10010", 6);
	// ft_strlcpy(digit[103][3], "10001", 6);
	// ft_strlcpy(digit[103][4], "01110", 6);

	// ft_strlcpy(digit[104][0], "10001", 6);
	// ft_strlcpy(digit[104][1], "10001", 6);
	// ft_strlcpy(digit[104][2], "11111", 6);
	// ft_strlcpy(digit[104][3], "10001", 6);
	// ft_strlcpy(digit[104][4], "10001", 6);

	// ft_strlcpy(digit[105][0], "11111", 6);
	// ft_strlcpy(digit[105][1], "00100", 6);
	// ft_strlcpy(digit[105][2], "00100", 6);
	// ft_strlcpy(digit[105][3], "00100", 6);
	// ft_strlcpy(digit[105][4], "11111", 6);

	// ft_strlcpy(digit[106][0], "11111", 6);
	// ft_strlcpy(digit[106][1], "00010", 6);
	// ft_strlcpy(digit[106][2], "00010", 6);
	// ft_strlcpy(digit[106][3], "10010", 6);
	// ft_strlcpy(digit[106][4], "01100", 6);

	// ft_strlcpy(digit[107][0], "10010", 6);
	// ft_strlcpy(digit[107][1], "10100", 6);
	// ft_strlcpy(digit[107][2], "11000", 6);
	// ft_strlcpy(digit[107][3], "10100", 6);
	// ft_strlcpy(digit[107][4], "10010", 6);

	// ft_strlcpy(digit[108][0], "10000", 6);
	// ft_strlcpy(digit[108][1], "10000", 6);
	// ft_strlcpy(digit[108][2], "10000", 6);
	// ft_strlcpy(digit[108][3], "10000", 6);
	// ft_strlcpy(digit[108][4], "11110", 6);

	// ft_strlcpy(digit[109][0], "10001", 6);
	// ft_strlcpy(digit[109][1], "11011", 6);
	// ft_strlcpy(digit[109][2], "10101", 6);
	// ft_strlcpy(digit[109][3], "10001", 6);
	// ft_strlcpy(digit[109][4], "10001", 6);

	// ft_strlcpy(digit[110][0], "10001", 6);
	// ft_strlcpy(digit[110][1], "11001", 6);
	// ft_strlcpy(digit[110][2], "10101", 6);
	// ft_strlcpy(digit[110][3], "10011", 6);
	// ft_strlcpy(digit[110][4], "10001", 6);

	// ft_strlcpy(digit[111][0], "01110", 6);
	// ft_strlcpy(digit[111][1], "10001", 6);
	// ft_strlcpy(digit[111][2], "10001", 6);
	// ft_strlcpy(digit[111][3], "10001", 6);
	// ft_strlcpy(digit[111][4], "01110", 6);

	// ft_strlcpy(digit[112][0], "01110", 6);
	// ft_strlcpy(digit[112][1], "10001", 6);
	// ft_strlcpy(digit[112][2], "11110", 6);
	// ft_strlcpy(digit[112][3], "10000", 6);
	// ft_strlcpy(digit[112][4], "10000", 6);

	// ft_strlcpy(digit[113][0], "01110", 6);
	// ft_strlcpy(digit[113][1], "10001", 6);
	// ft_strlcpy(digit[113][2], "10101", 6);
	// ft_strlcpy(digit[113][3], "10010", 6);
	// ft_strlcpy(digit[113][4], "01101", 6);

	// ft_strlcpy(digit[114][0], "11110", 6);
	// ft_strlcpy(digit[114][1], "10001", 6);
	// ft_strlcpy(digit[114][2], "11110", 6);
	// ft_strlcpy(digit[114][3], "10100", 6);
	// ft_strlcpy(digit[114][4], "10010", 6);

	// ft_strlcpy(digit[115][0], "01110", 6);
	// ft_strlcpy(digit[115][1], "10000", 6);
	// ft_strlcpy(digit[115][2], "01110", 6);
	// ft_strlcpy(digit[115][3], "00001", 6);
	// ft_strlcpy(digit[115][4], "01110", 6);

	// ft_strlcpy(digit[116][0], "11111", 6);
	// ft_strlcpy(digit[116][1], "00100", 6);
	// ft_strlcpy(digit[116][2], "00100", 6);
	// ft_strlcpy(digit[116][3], "00100", 6);
	// ft_strlcpy(digit[116][4], "00100", 6);

	// ft_strlcpy(digit[117][0], "10001", 6);
	// ft_strlcpy(digit[117][1], "10001", 6);
	// ft_strlcpy(digit[117][2], "10001", 6);
	// ft_strlcpy(digit[117][3], "10001", 6);
	// ft_strlcpy(digit[117][4], "01110", 6);

	// ft_strlcpy(digit[118][0], "10001", 6);
	// ft_strlcpy(digit[118][1], "10001", 6);
	// ft_strlcpy(digit[118][2], "01010", 6);
	// ft_strlcpy(digit[118][3], "01010", 6);
	// ft_strlcpy(digit[118][4], "00100", 6);

	// ft_strlcpy(digit[119][0], "10001", 6);
	// ft_strlcpy(digit[119][1], "10001", 6);
	// ft_strlcpy(digit[119][2], "10101", 6);
	// ft_strlcpy(digit[119][3], "11011", 6);
	// ft_strlcpy(digit[119][4], "10001", 6);

	// ft_strlcpy(digit[120][0], "10001", 6);
	// ft_strlcpy(digit[120][1], "01010", 6);
	// ft_strlcpy(digit[120][2], "00100", 6);
	// ft_strlcpy(digit[120][3], "01010", 6);
	// ft_strlcpy(digit[120][4], "10001", 6);

	// ft_strlcpy(digit[121][0], "10001", 6);
	// ft_strlcpy(digit[121][1], "01010", 6);
	// ft_strlcpy(digit[121][2], "00100", 6);
	// ft_strlcpy(digit[121][3], "00100", 6);
	// ft_strlcpy(digit[121][4], "00100", 6);

	// ft_strlcpy(digit[122][0], "11111", 6);
	// ft_strlcpy(digit[122][1], "00010", 6);
	// ft_strlcpy(digit[122][2], "00100", 6);
	// ft_strlcpy(digit[122][3], "01000", 6);
	// ft_strlcpy(digit[122][4], "11111", 6);






	ft_strlcpy(digit[97][0], "00000", 6);
	ft_strlcpy(digit[97][1], "01111", 6);
	ft_strlcpy(digit[97][2], "00001", 6);
	ft_strlcpy(digit[97][3], "01111", 6);
	ft_strlcpy(digit[97][4], "01111", 6);

	ft_strlcpy(digit[98][0], "10000", 6);
	ft_strlcpy(digit[98][1], "10000", 6);
	ft_strlcpy(digit[98][2], "11110", 6);
	ft_strlcpy(digit[98][3], "10010", 6);
	ft_strlcpy(digit[98][4], "11110", 6);

	ft_strlcpy(digit[99][0], "00000", 6);
	ft_strlcpy(digit[99][1], "01110", 6);
	ft_strlcpy(digit[99][2], "10000", 6);
	ft_strlcpy(digit[99][3], "10000", 6);
	ft_strlcpy(digit[99][4], "01110", 6);

	ft_strlcpy(digit[100][0], "00001", 6);
	ft_strlcpy(digit[100][1], "00001", 6);
	ft_strlcpy(digit[100][2], "01111", 6);
	ft_strlcpy(digit[100][3], "01001", 6);
	ft_strlcpy(digit[100][4], "01111", 6);

	ft_strlcpy(digit[101][0], "00000", 6);
	ft_strlcpy(digit[101][1], "01110", 6);
	ft_strlcpy(digit[101][2], "11110", 6);
	ft_strlcpy(digit[101][3], "10000", 6);
	ft_strlcpy(digit[101][4], "01110", 6);

	ft_strlcpy(digit[102][0], "00011", 6);
	ft_strlcpy(digit[102][1], "00100", 6);
	ft_strlcpy(digit[102][2], "01110", 6);
	ft_strlcpy(digit[102][3], "00100", 6);
	ft_strlcpy(digit[102][4], "00100", 6);

	ft_strlcpy(digit[103][0], "00111", 6);
	ft_strlcpy(digit[103][1], "01001", 6);
	ft_strlcpy(digit[103][2], "00111", 6);
	ft_strlcpy(digit[103][3], "00001", 6);
	ft_strlcpy(digit[103][4], "01110", 6);

	
	ft_strlcpy(digit[104][0], "01000", 6);
	ft_strlcpy(digit[104][1], "01000", 6);
	ft_strlcpy(digit[104][2], "01110", 6);
	ft_strlcpy(digit[104][3], "01010", 6);
	ft_strlcpy(digit[104][4], "01010", 6);

	ft_strlcpy(digit[105][0], "00100", 6);
	ft_strlcpy(digit[105][1], "00000", 6);
	ft_strlcpy(digit[105][2], "00100", 6);
	ft_strlcpy(digit[105][3], "00100", 6);
	ft_strlcpy(digit[105][4], "00100", 6);

	ft_strlcpy(digit[106][0], "00010", 6);
	ft_strlcpy(digit[106][1], "00000", 6);
	ft_strlcpy(digit[106][2], "00010", 6);
	ft_strlcpy(digit[106][3], "01010", 6);
	ft_strlcpy(digit[106][4], "00100", 6);

	ft_strlcpy(digit[107][0], "00000", 6);
	ft_strlcpy(digit[107][1], "01010", 6);
	ft_strlcpy(digit[107][2], "01100", 6);
	ft_strlcpy(digit[107][3], "01100", 6);
	ft_strlcpy(digit[107][4], "01010", 6);

	ft_strlcpy(digit[108][0], "01000", 6);
	ft_strlcpy(digit[108][1], "01000", 6);
	ft_strlcpy(digit[108][2], "01000", 6);
	ft_strlcpy(digit[108][3], "01000", 6);
	ft_strlcpy(digit[108][4], "00110", 6);

	ft_strlcpy(digit[109][0], "00000", 6);
	ft_strlcpy(digit[109][1], "10001", 6);
	ft_strlcpy(digit[109][2], "11011", 6);
	ft_strlcpy(digit[109][3], "10101", 6);
	ft_strlcpy(digit[109][4], "10001", 6);

	ft_strlcpy(digit[110][0], "00000", 6);
	ft_strlcpy(digit[110][1], "01000", 6);
	ft_strlcpy(digit[110][2], "01110", 6);
	ft_strlcpy(digit[110][3], "01010", 6);
	ft_strlcpy(digit[110][4], "01010", 6);

	ft_strlcpy(digit[111][0], "00000", 6);
	ft_strlcpy(digit[111][1], "01110", 6);
	ft_strlcpy(digit[111][2], "10001", 6);
	ft_strlcpy(digit[111][3], "10001", 6);
	ft_strlcpy(digit[111][4], "01110", 6);

	ft_strlcpy(digit[112][0], "00000", 6);
	ft_strlcpy(digit[112][1], "01100", 6);
	ft_strlcpy(digit[112][2], "10010", 6);
	ft_strlcpy(digit[112][3], "11100", 6);
	ft_strlcpy(digit[112][4], "10000", 6);

	ft_strlcpy(digit[113][0], "00000", 6);
	ft_strlcpy(digit[113][1], "00111", 6);
	ft_strlcpy(digit[113][2], "01001", 6);
	ft_strlcpy(digit[113][3], "00111", 6);
	ft_strlcpy(digit[113][4], "00001", 6);

	ft_strlcpy(digit[114][0], "00000", 6);
	ft_strlcpy(digit[114][1], "01000", 6);
	ft_strlcpy(digit[114][2], "01110", 6);
	ft_strlcpy(digit[114][3], "01010", 6);
	ft_strlcpy(digit[114][4], "01000", 6);

	ft_strlcpy(digit[115][0], "00000", 6);
	ft_strlcpy(digit[115][1], "00110", 6);
	ft_strlcpy(digit[115][2], "01100", 6);
	ft_strlcpy(digit[115][3], "00010", 6);
	ft_strlcpy(digit[115][4], "01100", 6);

	ft_strlcpy(digit[116][0], "00000", 6);
	ft_strlcpy(digit[116][1], "01000", 6);
	ft_strlcpy(digit[116][2], "11100", 6);
	ft_strlcpy(digit[116][3], "01000", 6);
	ft_strlcpy(digit[116][4], "00110", 6);

	ft_strlcpy(digit[117][0], "00000", 6);
	ft_strlcpy(digit[117][1], "00000", 6);
	ft_strlcpy(digit[117][2], "10001", 6);
	ft_strlcpy(digit[117][3], "10001", 6);
	ft_strlcpy(digit[117][4], "01110", 6);

	ft_strlcpy(digit[118][0], "00000", 6);
	ft_strlcpy(digit[118][1], "00000", 6);
	ft_strlcpy(digit[118][2], "10001", 6);
	ft_strlcpy(digit[118][3], "01010", 6);
	ft_strlcpy(digit[118][4], "00100", 6);

	ft_strlcpy(digit[119][0], "00000", 6);
	ft_strlcpy(digit[119][1], "10001", 6);
	ft_strlcpy(digit[119][2], "10101", 6);
	ft_strlcpy(digit[119][3], "11011", 6);
	ft_strlcpy(digit[119][4], "10001", 6);

	ft_strlcpy(digit[120][0], "00000", 6);
	ft_strlcpy(digit[120][1], "01010", 6);
	ft_strlcpy(digit[120][2], "00100", 6);
	ft_strlcpy(digit[120][3], "01010", 6);
	ft_strlcpy(digit[120][4], "01010", 6);

	ft_strlcpy(digit[121][0], "00000", 6);
	ft_strlcpy(digit[121][1], "10001", 6);
	ft_strlcpy(digit[121][2], "01010", 6);
	ft_strlcpy(digit[121][3], "00100", 6);
	ft_strlcpy(digit[121][4], "00100", 6);

	ft_strlcpy(digit[122][0], "00000", 6);
	ft_strlcpy(digit[122][1], "11110", 6);
	ft_strlcpy(digit[122][2], "00100", 6);
	ft_strlcpy(digit[122][3], "01000", 6);
	ft_strlcpy(digit[122][4], "11110", 6);













	
	ft_strlcpy(digit[123][0], "01110", 6);
	ft_strlcpy(digit[123][1], "01000", 6);
	ft_strlcpy(digit[123][2], "11000", 6);
	ft_strlcpy(digit[123][3], "01000", 6);
	ft_strlcpy(digit[123][4], "01110", 6);

	ft_strlcpy(digit[124][0], "00100", 6);
	ft_strlcpy(digit[124][1], "00100", 6);
	ft_strlcpy(digit[124][2], "00100", 6);
	ft_strlcpy(digit[124][3], "00100", 6);
	ft_strlcpy(digit[124][4], "00100", 6);

	ft_strlcpy(digit[125][0], "01110", 6);
	ft_strlcpy(digit[125][1], "00010", 6);
	ft_strlcpy(digit[125][2], "00011", 6);
	ft_strlcpy(digit[125][3], "00010", 6);
	ft_strlcpy(digit[125][4], "01110", 6);

	ft_strlcpy(digit[126][0], "00000", 6);
	ft_strlcpy(digit[126][1], "01000", 6);
	ft_strlcpy(digit[126][2], "10101", 6);
	ft_strlcpy(digit[126][3], "00010", 6);
	ft_strlcpy(digit[126][4], "00000", 6);

	ft_strlcpy(digit[127][0], "00000", 6);
	ft_strlcpy(digit[127][1], "00000", 6);
	ft_strlcpy(digit[127][2], "00000", 6);
	ft_strlcpy(digit[127][3], "00000", 6);
	ft_strlcpy(digit[127][4], "00000", 6);
}