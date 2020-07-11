/*---------------------------------------------------------------------------*/
/* btree.h                                                                   */
/* copyright (c) innovaphone 2001                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#ifndef _BTREE_H_
#define _BTREE_H_

NAMESPACE_BEGIN

class btree {
    int count;

    virtual int btree_compare(void * key) = 0;
    virtual int btree_compare(class btree * b) = 0;
    virtual void leak_check() {};

    class btree * rotate_left();
    class btree * rotate_right();

protected:
    class btree * left;
    class btree * right;

public:
    btree();
    virtual ~btree() {};
    class btree * btree_find(const void * key);
    class btree * btree_find_first_left(const void * key);
    class btree * btree_find_first_right(const void * key);
    class btree * btree_find_next_left(const void * key);
    class btree * btree_find_next_right(const void * key);
    class btree * btree_find_left();
    class btree * btree_find_right();
    class btree * btree_put(class btree * in);
    class btree * btree_put(class btree * in, bool & before, class btree * & p);
    class btree * btree_get(class btree * out);
    int get_count() { return count; };
    void print_tree(int level);
    void tree_leak_check();

    static class btree * btree_find(class btree * tree, const void * key) { return tree ? tree->btree_find(key) : 0; };
    static class btree * btree_find_first_left(class btree * tree, const void * key) { return tree ? tree->btree_find_first_left(key) : 0; };
    static class btree * btree_find_first_right(class btree * tree, const void * key) { return tree ? tree->btree_find_first_right(key) : 0; };
    static class btree * btree_find_next_left(class btree * tree, const void * key) { return tree ? tree->btree_find_first_left(key) : 0; };
    static class btree * btree_find_next_right(class btree * tree, const void * key) { return tree ? tree->btree_find_next_right(key) : 0; };
    static class btree * btree_find_left(class btree * tree) { return tree ? tree->btree_find_left() : 0; };
    static class btree * btree_find_right(class btree * tree) { return tree ? tree->btree_find_right() : 0; };
    static void btree_put(class btree * & tree, class btree * in) { if (tree) tree = tree->btree_put(in); else tree = in; };
    static void btree_put(class btree * & tree, class btree * in, bool & before, class btree * & p) { if (tree) { tree->btree_put(in, before, p); } else { before = false; p = 0; } };
    static void btree_get(class btree * & tree, class btree * out) { tree = tree->btree_get(out); };
    static int get_count(class btree * tree) { return tree ? tree->count : 0; };
    void tree_leak_check(class btree * tree) { if (tree) tree->tree_leak_check(); };
};

NAMESPACE_END

#endif
