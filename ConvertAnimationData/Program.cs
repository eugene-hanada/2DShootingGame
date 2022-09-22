// See https://aka.ms/new-console-template for more information

class App
{
	public static void Main(string[] args)
	{
		if (args.Length < 1)
        {
			return;
        }
		var d = new ConvertAnimationData.AnimationData(args[0], args[1]);
	}

}
