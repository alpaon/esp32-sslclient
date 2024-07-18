import re
import click


def split_certificates(input_file, output_prefix):
    with open(input_file, "r") as f:
        content = f.read()

    # 정규 표현식을 사용하여 인증서를 찾습니다
    cert_pattern = re.compile(
        r"-----BEGIN CERTIFICATE-----.*?-----END CERTIFICATE-----", re.DOTALL
    )
    certificates = cert_pattern.findall(content)

    # 각 인증서를 별도의 파일로 저장합니다
    for i, cert in enumerate(certificates):
        output_file = f"{output_prefix}_{i+1}.pem"
        with open(output_file, "w") as f:
            f.write(cert)
        click.echo(f"Certificate {i+1} saved to {output_file}")


@click.command()
@click.argument("input_file", type=click.Path(exists=True))
@click.option(
    "--output-prefix", "-o", default="cert", help="Prefix for output certificate files"
)
def main(input_file, output_prefix):
    """
    Split a PEM file containing multiple certificates into separate PEM files.

    INPUT_FILE: Path to the input PEM file containing multiple certificates.
    """
    click.echo(f"Processing file: {input_file}")
    split_certificates(input_file, output_prefix)
    click.echo("Certificate splitting completed.")


if __name__ == "__main__":
    main()
