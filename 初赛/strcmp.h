char strMatch( const char *str1, const char *str2)  
{  
	//str1 待检测字符串  str2 匹配条件字符串
	//设计思想：以'*'为分隔符分段比较测试
	int iLen1 = strlen(str1);  
	int iLen2 = strlen(str2);
	int i=0, j=0, k=0, l , m , n;  

	//查找匹配条件字符串最后一个非'*'字符的位置
	for(l=0 , n=0; l<iLen2; l++)
	{
		if(str2[l]!='*')n=l; 
	}

	while(i<iLen1&&j<iLen2)
	{	
		//指到匹配条件字符串'*'后的第一个字符，并备份i,j;/////
		while(j<iLen2)										//	
		{													//
			if(str2[j]=='*')	{ k=1;  j++;}				//	
			else	{ l=j; m=i; break; }					//			
		}													//
		//////////////////////////////////////////////////////

		//////////段测试//////////////////////////////////////
		while(i<iLen1&&j<iLen2)								//				
		{													//	
			if(str2[j]=='*')break;							//
															//		
			if(str1[i]==str2[j]||str2[j]=='?'){i++;j++;}	//
			else											//
			{												//
				if(k==1){m++; i=m; j=l;}					//	
				else return 0;								//
			}												//	
		}													//		
		//////////////////////////////////////////////////////

		//如果被测字符串还没到尾，条件字串已到尾且最后一个不是'*'与k==1，则
		if(i<iLen1&&j==iLen2&&str2[j-1]!='*'&&k==1){m++; i=m; j=l;}
	}
	//条件字串（最后的'*'不算)与被测回全匹配 或 被测串没到尾但条件串最后是'*'
	if(((i==iLen1&&n+1==j)||(i<iLen1)&&j!=0&&str2[j-1]=='*'))return 1;
	else
		return 0;
}