using System.Xml.Linq;


namespace TextureDataConvert
{
	internal class DataLoader
	{
		private string fileName_;
		private AtlasData? atlas_;
		private int sum_ = 0;

		public DataLoader(string fileName)
		{
			fileName_ = fileName;
			Load(fileName_);
		}

		bool Load(string fnameName)
		{
			Console.WriteLine(fnameName + "を読み込みます");
			XElement xml;
			try
			{
				xml = XElement.Load(fnameName);
			}
			catch (Exception )
			{
				Console.WriteLine("ファイルロードに失敗しました");
				return false;
			}

			atlas_ = new AtlasData(xml);
			sum_ = atlas_.CalcSum();
			return true;
		}

		public bool Export(string fileName)
		{
			Console.WriteLine(fileName + "に出力します");
			var file =  File.Create(fileName);
			var bw = new BinaryWriter(file);

			// シグネチャを書き込む
			var sig = new char[4];
			sig[0] = 't';
			sig[1] = 'd';
			sig[2] = 'a';
			sig[3] = 't';
			bw.Write(sig);

			// Sum値を出力
			bw.Write(sum_);
			
			if (atlas_ == null)
			{
				throw new Exception("atlasがnullです");
			}

			atlas_.Write(bw);
			
			file.Close();
			return true;
		}

		public bool Export()
		{
			return Export(fileName_.Substring(0, fileName_.Length - 4) + ".tdat");
		}

		

		
		
	}
}
