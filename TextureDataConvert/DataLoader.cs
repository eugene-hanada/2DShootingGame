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
		private string imageFileName_;
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
			bw.Write(imageFileName_.Length);
			bw.Write(imageFileName_.ToCharArray());

			foreach (var data in textureData_)
			{
				bw.Write(data.Key.Length);
				bw.Write(data.Key.ToCharArray());
				foreach(var texdata in data.Value)
				{
					texdata.Write(bw);
				}
			}

			file.Close();
			return true;
		}

		private void CalcSub()
		{
			foreach (var data in textureData_)
			{
				sum_ += data.Value.ToArray().Length;
			}
		}

		private class TextureData
		{
			private Vector2 pos_;
			private Vector2 wh_;

			public TextureData(XElement? sprite)
			{
				if (sprite == null)
				{
					throw new ArgumentNullException(nameof(sprite));
				}

				var x = sprite.Attribute("x");
				var y = sprite.Attribute("y");
				if (x == null || y == null)
				{
					throw new ArgumentNullException("xもしくはyの値がありません");
				}
				pos_ = new Vector2(Int32.Parse(x.Value), Int32.Parse(y.Value));

				var w = sprite.Attribute("w");
				var h = sprite.Attribute("h");

				if (w == null || h == null)
				{
					throw new ArgumentNullException("wもしくはhの値がありません");
				}
				wh_ = new Vector2(Int32.Parse(w.Value), Int32.Parse(h.Value));

			}

			public void Write(BinaryWriter bw)
			{
				pos_.Write(bw);
				wh_.Write(bw);
			}

		}
		
	}
}
