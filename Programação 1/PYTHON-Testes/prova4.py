def main():
	s = str(input())
	up = True
	news = ""
	for i in range(len(s)):
		if (s[i].isalpha()):
			if up:
				news += s[i].upper()
				up = False
			else:
				news += s[i].lower()
				up = True
			
		else:
			news += s[i]

	print(news)
main()