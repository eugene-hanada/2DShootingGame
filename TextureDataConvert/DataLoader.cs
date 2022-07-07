using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Text.RegularExpressions;

namespace TextureDataConvert
{
	internal class DataLoader
	{
		private string fileName_;
		private string? imageFileName_;
		private Dictionary<string,List<TextureData>> textureData_;
		private int sum_ = 0;

		public DataLoader(string fileName)
		{
			fileName_ = fileName;
			textureData_ = new Dictionary<string, List<TextureData>>();
			Load(fileName_);
		}

		bool Load(string fnameName)
		{
			XElement xml;
			try
			{
				xml = XElement.Load(fnameName);
			}
			catch (Exception ex)
			{
				Console.WriteLine(ex.Message);
				return false;
			}

			var img = xml.Attribute("imagePath");
			if (img == null)
			{
				return false;
			}

			imageFileName_ = img.Value;

			foreach (var sp in xml.Elements())
			{
				var nameAtr = sp.Attribute("n");
				if (nameAtr != null)
				{
					var name = nameAtr.Value;
					if (name == null)
					{
						break;
					}
					name = name.Substring(0,name.Length - 4);

					// 0から9で区切る
					string ptn = "[0-9]";
					var result = Regex.Split(name,ptn);
					string keyName = result[0];

					// キーがすでにあるかチェック
					if (!textureData_.ContainsKey(keyName))
					{
						textureData_.Add(keyName, new List<TextureData>());
					}

					textureData_[keyName].Add(new TextureData(sp));

				}
				
			
			}

			CalcSub();
			return true;
		}

		public bool Export(string fileName)
		{
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

			// 画像ファイル名を出力
			if (imageFileName_ == null)
			{
				throw new Exception("画像ファイル名が有りません");
			}

			bw.Write(imageFileName_.Length);
			bw.Write(imageFileName_.ToCharArray());

			foreach (var data in textureData_)
			{
				bw.Write(data.Key.Length);
				bw.Write(data.Key.ToCharArray());
				bw.Write(data.Value.ToArray().Length);
				foreach(var texdata in data.Value)
				{
					texdata.Write(bw);
				}
			}

			file.Close();
			return true;
		}

		public bool Export()
		{
			return Export(fileName_.Substring(0, fileName_.Length - 4) + ".tdat");
		}

		private void CalcSub()
		{
			foreach (var data in textureData_)
			{
				sum_ += data.Value.ToArray().Length;
			}
		}

		
		
	}
}
