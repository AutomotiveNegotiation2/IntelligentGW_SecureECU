/*
 * CC0 (Public domain) - see licenses/CC0 file for details
 * This code is based on ccan/strset.c.
 */

#include <map.h>
#include <types/short_types.h>
#include <str.h>
#include <ilog.h>
#include <stddef.h>

/* Closest member to this in a non-empty map. */
static struct map *closest(struct map *n, const u8 *bytes, size_t len)
{
	/* Anything with NULL value is a node. */
	while (!n->v) {
		u8 direction = 0;

		if (n->u.n->byte_num < len) {
			u8 c = bytes[n->u.n->byte_num];
			direction = (c >> n->u.n->bit_num) & 1U;
		}
		n = &n->u.n->child[direction];
	}
	return n;
}

struct map_node *strmap_get(const struct map *mapp, const char *member)
{
	struct map *n;

	/* Not empty map? */
	if (mapp) {
		n = closest((struct map *) mapp, (const u8 *) member,
			    strlen(member));
		if (streq(member, (const char *) n->u.s)) {
			return n->v;
		}
	}
	return NULL;
}

struct map_node *u32map_get(const struct map *mapp, u32 member)
{
	struct map *n;

	/* Not empty map? */
	if (mapp) {
		n = closest((struct map *) mapp, (const u8 *) &member,
			    sizeof(u32));
		if (member == (u32) n->u.s) {
			return n->v;
		}
	}
	return NULL;
}

const u8 *str_get_bytes(struct map *mapp)
{
	return (const u8 *) mapp->u.s;
}

const u8 *u32_get_bytes(struct map *mapp)
{
	return (const u8 *) &mapp->u.s;
}

struct map *map_add(struct map *mapp, const void *member, const u8 *bytes,
		    size_t len, struct map_node *newn,
		    const u8 *(*get_bytes)(struct map *))
{
	struct map *n;
	size_t byte_num;
	u8 bit_num, new_dir;
	const u8 *s;

	/* Empty map? */
	if (!mapp) {
		mapp = &newn->child[0];
		mapp->u.s = member;
		mapp->v = newn;
		return mapp;
	}

	/* Find closest existing member. */
	n = closest(mapp, bytes, len);

	/* Find where they differ. */
	s = get_bytes(n);
	for (byte_num = 0; s[byte_num] == bytes[byte_num]; byte_num++) {
		if (byte_num == len) {
			/* All identical! */
			return NULL;
		}
	}

	/* Find which bit differs (if we had ilog8, we'd use it) */
	bit_num = (u8) (ilog32_nz((s32) (s[byte_num] ^ bytes[byte_num])) - 1);

	/* Which direction do we go at this bit? */
	new_dir = ((bytes[byte_num]) >> bit_num) & 1U;

	newn->byte_num = byte_num;
	newn->bit_num = bit_num;
	newn->child[new_dir].v = newn;
	newn->child[new_dir].u.s = member;

	/* Find where to insert: not closest, but first which differs! */
	n = mapp;
	while (!n->v) {
		u8 direction = 0;

		if (n->u.n->byte_num > byte_num) {
			break;
		}
		/* Subtle: bit numbers are "backwards" for comparison */
		if ((n->u.n->byte_num == byte_num) && (n->u.n->bit_num <
						       bit_num)) {
			break;
		}

		if (n->u.n->byte_num < len) {
			u8 c = bytes[n->u.n->byte_num];
			direction = (c >> n->u.n->bit_num) & 1U;
		}
		n = &n->u.n->child[direction];
	}

	newn->child[!new_dir] = *n;
	n->u.n = newn;
	n->v = NULL;
	return mapp;
}

static sbool str_iterate(struct map n,
			 sbool (*handle)(const char *, struct map_node *, void *),
			 const void *data)
{
	if (n.v) {
		return handle((const char *) n.u.s, n.v, (void *) data);
	}

	return str_iterate(n.u.n->child[0], handle, data)
	       && str_iterate(n.u.n->child[1], handle, data);
}

void strmap_iterate_(const struct map *mapp,
		     sbool (*handle)(const char *, struct map_node *, void *),
		     const void *data)
{
	/* Empty map? */
	if (!mapp) {
		return;
	}

	str_iterate(*mapp, handle, data);
}

static sbool u32_iterate(struct map n,
			 sbool (*handle)(u32, struct map_node *, void *),
			 const void *data)
{
	if (n.v) {
		return handle((u32) n.u.s, n.v, (void *) data);
	}

	return u32_iterate(n.u.n->child[0], handle, data)
	       && u32_iterate(n.u.n->child[1], handle, data);
}

void u32map_iterate_(const struct map *mapp,
		     sbool (*handle)(u32, struct map_node *, void *),
		     const void *data)
{
	/* Empty map? */
	if (!mapp) {
		return;
	}

	u32_iterate(*mapp, handle, data);
}

const struct map *strmap_prefix(const struct map *mapp, const char *prefix)
{
	const struct map *n, *top;
	size_t len = strlen(prefix);
	const u8 *bytes = (const u8 *) prefix;

	/* Empty map -> return empty map. */
	if (!mapp) {
		return mapp;
	}

	top = n = mapp;

	/* We walk to find the top, but keep going to check prefix matches. */
	while (!n->v) {
		u8 c = 0, direction;

		if (n->u.n->byte_num < len) {
			c = bytes[n->u.n->byte_num];
		}

		direction = (c >> n->u.n->bit_num) & 1U;
		n = &n->u.n->child[direction];
		if (c) {
			top = n;
		}
	}

	if (!strstarts((const char *) n->u.s, prefix)) {
		return NULL;
	}

	return top;
}
