/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enums.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 17:05:24 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 16:11:57 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum		e_event_code
{
	MOUSE_PRESS_CODE = 4,
	MOUSE_MOVE_CODE = 6,
	KEY_PRESS_CODE = 2,
	KEY_RELEASE_CODE = 3,
	RED_BUTTON_CODE = 17,
	DESTROY_EVENT = 1L << 17,
}					t_event_code;

typedef enum		e_ft_mlx_hooks
{
	NO_EVENT_HOOK = 0,
	MOUSE_PRESS_HOOK = 1,
	MOUSE_MOVE_HOOK = 2,
	KEY_PRESS_HOOK = 4,
	RED_BUTTON_HOOK = 8,
}					t_ft_mlx_hooks;

typedef enum		e_key_code
{
	ZOOM_IN = 69,
	ZOOM_OUT = 78,
	SPACE = 49,
	NUM_LOCK_9 = 92,
	NUM_LOCK_8 = 91,
	NUM_LOCK_7 = 89,
	NUM_LOCK_6 = 88,
	NUM_LOCK_5 = 87,
	NUM_LOCK_4 = 86,
	NUM_LOCK_3 = 85,
	NUM_LOCK_2 = 84,
	NUM_LOCK_1 = 83,
	NUM_LOCK_0 = 82,
	RIGHT_ARROW = 124,
	LEFT_ARROW = 123,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
	ESCAPE = 53,
	AKEY = 0,
	SKEY = 1,
	DKEY = 2,
	QKEY = 12,
	WKEY = 13,
	EKEY = 14,
	NUMZERO = 82,
	NUMONE = 83,
	NUMTWO = 84,
	NUMTHREE = 85,
	NUMFOUR = 86,
	NUMFIVE = 87,
	NUMSIX = 88,
	NUMSEVEN = 89,
	NUMEIGHT = 91,
	NUMNINE = 92,
	NUMCLEAR = 71,
	NUMIS = 81,
	NUMENTER = 76,
	NUMPLUS = 69,
	NUMMINUS = 78,
	NUMSLASH = 75,
	NUMSTAR = 67,
	PLUS = 24,
	MINUS = 27,
	F10 = 109,
	F12 = 111,
}					t_key_code;

#endif
