/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

#ifndef fooconditionhfoo
#define fooconditionhfoo

/***
  This file is part of systemd.

  Copyright 2010 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdbool.h>

#include "list.h"

typedef enum ConditionType {
        CONDITION_PATH_EXISTS,
        CONDITION_PATH_IS_DIRECTORY,
        CONDITION_DIRECTORY_NOT_EMPTY,
        CONDITION_KERNEL_COMMAND_LINE,
        CONDITION_VIRTUALIZATION,
        CONDITION_NULL,
        _CONDITION_TYPE_MAX,
        _CONDITION_TYPE_INVALID = -1
} ConditionType;

typedef struct Condition {
        ConditionType type;
        char *parameter;

        bool trigger:1;
        bool negate:1;

        LIST_FIELDS(struct Condition, conditions);
} Condition;

Condition* condition_new(ConditionType type, const char *parameter, bool trigger, bool negate);
void condition_free(Condition *c);
void condition_free_list(Condition *c);

bool condition_test(Condition *c);
bool condition_test_list(Condition *c);

void condition_dump(Condition *c, FILE *f, const char *prefix);
void condition_dump_list(Condition *c, FILE *f, const char *prefix);

const char* condition_type_to_string(ConditionType t);
int condition_type_from_string(const char *s);

#endif
