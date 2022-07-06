// See https://aka.ms/new-console-template for more information

namespace TextureDataConvert
{
	class App
	{
		public static void Main(string[] args)
		{
			var loader = new DataLoader(args[0]);
			
			if (args.Length > 1)
			{
				loader.Export(args[1]);
			}
			else
			{

			}

		}
	}
}