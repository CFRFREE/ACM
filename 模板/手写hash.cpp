static struct HashTable {
	int head[HASHMOD];
	int key[HASHSIZE + 10], val[HASHSIZE + 10], nxt[HASHSIZE + 10], cnt;
	void clear() {
		cnt = 0;
		memset(head, 0, sizeof(head));
	}
	bool count(const int k) {
		for (int i = head[k % HASHMOD]; i; i = nxt[i])
			if (key[i] == k) return true;
		return false;
	}
	int operator[](const int k) {
		for (int i = head[k % HASHMOD]; i; i = nxt[i]) {
			if (key[i] == k) return val[i];
		}
		return 0;
	}
	void add(int k, int v) {
		int p = k % HASHMOD;
		nxt[++cnt] = head[p];
		key[cnt] = k; val[cnt] = v;
		head[p] = cnt;
	}
} tb;